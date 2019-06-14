package tk.voidx.instrumentbuddy;

import android.Manifest;
import android.content.pm.*;
import android.media.*;
import android.support.v4.app.*;
import android.support.v4.content.*;
import java.util.*;

/**
 * A fragment which depends on microphone input for displaying the current loudest frequency.
 */
public abstract class MeasuringFragment extends Fragment {
    /**
     * Called each time when new microphone data is available to process.
     */
    protected abstract void onNewFrequencyAvailable();

    /**
     * @return The loudest frequency present in the buffer.
     */
    public float getFrequency() {
        // Don't crash if microphone permission wasn't given.
        if (ar == null)
            return 0;
        // Get samples.
        ar.read(rawSamples, 0, buffer);
        for (int i = 0; i < buffer; ++i)
            samples[i] = rawSamples[i] * NORMALIZE;
        // Autocorrelation of the signal.
        float peak = Float.NEGATIVE_INFINITY;
        int peakIndex = -1;
        for (int i = minPeriod; i < maxPeriod; ++i) {
            float sum = 0;
            for (int j = 0; j < buffer - i; ++j)
                sum += samples[j] * samples[j + i];
            // Find the peak frequency.
            if (sum > peak) {
                peakIndex = i;
                peak = sum;
            }
        }
        return sampleRate / (float)peakIndex;
    }

    /**
     * Timing for buffer availability.
     */
    private TimerTask updater = new TimerTask() {
        public void run() {
            onNewFrequencyAvailable();
        }
    };

    @Override
    public void onResume() {
        super.onResume();
        // Ask for permission and start recording.
        if (ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED)
            ActivityCompat.requestPermissions(getActivity(), new String[]{Manifest.permission.RECORD_AUDIO}, REQUEST_MICROPHONE);
        super.onStart();
        // Start recording with the minimal or required buffer size.
        for (int rate : new int[] {48000, 44100, 22050, 16000, 11025, 8000}) {
            int bufferSize = AudioRecord.getMinBufferSize(rate, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT);
            if (bufferSize > 0) {
                sampleRate = rate;
                break;
            }
        }
        minPeriod = sampleRate / MAX_FREQ;
        maxPeriod = sampleRate / MIN_FREQ;
        buffer = Math.max(AudioRecord.getMinBufferSize(sampleRate, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT),
                44100 / UPDATE_RATE - (44100 / UPDATE_RATE) % 2);
        rawSamples = new short[buffer];
        samples = new float[buffer];
        ar = new AudioRecord(MediaRecorder.AudioSource.MIC, sampleRate, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT, buffer);
        try {
            ar.startRecording();
        } catch (Exception e) {
            ar = null;
        }
        // Start looping buffer availability.
        timer.scheduleAtFixedRate(updater, buffer * 1000 / sampleRate, 1000 / UPDATE_RATE);
    }

    @Override
    public void onPause() {
        super.onPause();
        // Stop listening on the microphone.
        if (ar != null)
            ar.stop();
        // Stop buffer availability loop.
        timer.cancel();
        timer.purge();
    }

    /**
     * Request ID for microphone permission.
     */
    private static final int REQUEST_MICROPHONE = 1;
    /**
     * Note updates per second.
     */
    private static final int UPDATE_RATE = 4;
    /**
     * Minimum frequency to check for.
     */
    private static final int MIN_FREQ = 25;
    /**
     * Maximum frequency to check for.
     */
    private static final int MAX_FREQ = 5000;
    /**
     * Short to float sample multiplication.
     */
    private static final float NORMALIZE = 1f / Short.MAX_VALUE;
    /**
     * Microphone input.
     */
    private static AudioRecord ar = null;
    /**
     * Note update timer.
     */
    Timer timer = new Timer("Note updater");
    /**
     * Target sample rate.
     */
    private int sampleRate = -1;
    /**
     * Frequency analysis lower bound.
     */
    private int minPeriod;
    /**
     * Frequency analysis upper bound.
     */
    private int maxPeriod;
    /**
     * Audio buffer size.
     */
    private int buffer;
    /**
     * Sample holder before frequency calculations.
     */
    private short[] rawSamples;
    /**
     * Sample holder in float.
     */
    private float[] samples;
}
