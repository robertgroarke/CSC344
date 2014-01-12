import java.io.*;

public class WavRearrange {
   
   // Adapted from Ed Foley's implementation of Dr Andrew Greensted's Java Wav
   // File I/O Libraries
   
   public static void main(String[] args)
    {
        try
        {
            double duration = 30.0;     // Duration of output file [seconds]
            
            // Open the wav file specified as the first argument
            WavFile wavFileIn = WavFile.openWavFile(new File("Grand_Theft_Ecstasy.wav"));       
            
            // Read sample rate [samples/second] of input file so we can use this value for output file
            int sampleRate = (int)(wavFileIn.getSampleRate());
            
            long numFramesIn = wavFileIn.getNumFrames();
            
            // Calculate the number of frames required for specified duration for easy reference
            long numFramesOut = (long)(duration*sampleRate);
            
            // Prepare an output file with the length and sample rate determined prior
            WavFile wavFileOut = WavFile.newWavFile(new File("New_Grand_Theft_Ecstasy.wav"), 2, numFramesOut, 16, sampleRate);
            
            // Get the number of audio channels in the wav file so that we may allocate buffer space accordingly
            int numChannels = wavFileIn.getNumChannels();

            //Create input buffer covering whole song for easy access.
            double[] bufferIn = new double[(int)(numFramesIn * numChannels)];
            
            //Create output buffer for new song. [0][] is left channel; [1][] is right.
            double[][] bufferOut = new double[numChannels][(int)(numFramesOut)];
            
            // read frames from input file to bufferIn
            wavFileIn.readFrames(bufferIn, (int)numFramesIn);
            
            // My Code to rearrange the original music into a new piece of music
            
            //Reverses the frames
            for( int i = 0; i<numFramesOut; i++) {              
               bufferOut[0][i] = bufferIn[(int)numFramesOut*2 - 2*i];
               bufferOut[1][i] = bufferIn[(int)numFramesOut*2 - 2*i-1];   
            }
            
            double[][] bufferSpliced = new double[numChannels][(int)(numFramesOut)];
            
            // Puts the second half of the frames in front
            for( int i = 0; i< (int)(numFramesOut/2); i++) {  
               bufferSpliced[0][i + (int)(numFramesOut/2)] = bufferOut[0][i];
               bufferSpliced[1][i + (int)(numFramesOut/2)] = bufferOut[1][i];
               
               bufferSpliced[0][i] = bufferOut[0][i + (int)(numFramesOut/2)];
               bufferSpliced[1][i] = bufferOut[1][i + (int)(numFramesOut/2)];
            }
            
            // write frames in bufferOut to our output file
            wavFileOut.writeFrames(bufferSpliced, (int)numFramesOut);
            
            // Close the wav files
            wavFileIn.close();
            wavFileOut.close();
        }
        catch (Exception e)
        {
            System.err.println(e);
        }
    }    
   
}
