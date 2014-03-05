import java.io.*;
import java.util.Random;

public class AlgorithmicComposition {
   
   // Adapted from Ed Foley's implementation of Dr Andrew Greensted's Java Wav
   // File I/O Libraries
   
   public static int randInt(int min, int max) {

    // Usually this can be a field rather than a method variable
    Random rand = new Random();

    // nextInt is normally exclusive of the top value,
    // so add 1 to make it inclusive
    int randomNum = rand.nextInt((max - min) + 1) + min;

    return randomNum;
}
   
   public static void main(String[] args)
    {
        try
        {
            double skip = 70.0;
            double duration = 60.0; // Duration of output file [seconds]
            double quartermeasure = 0.428547;
            double halfmeasure = 0.42857 * 2;     
            double measure = 0.42857 * 4;
            
            // Open the wav file specified as the first argument
            WavFile wavFileIn = WavFile.openWavFile(new File("DoTA.wav"));       
            
            // Read sample rate [samples/second] of input file so we can use this value for output file
            int sampleRate = (int)(wavFileIn.getSampleRate());
            
            long numFramesIn = wavFileIn.getNumFrames();
            
            // Calculate the number of frames required for specified duration for easy reference
            int numFramesSkip = (int)(skip*sampleRate*2);
            long numFramesOut = (long)(duration*sampleRate);
            long numFramesMeasure = (long)(measure*sampleRate);
            long numFramesHalfMeasure = (long)(halfmeasure*sampleRate);
            long numFramesQuarterMeasure = (long)(quartermeasure*sampleRate);
            
            // Prepare an output file with the length and sample rate determined prior
            WavFile wavFileOut = WavFile.newWavFile(new File("New_DoTA.wav"), 2, numFramesOut, 16, sampleRate);
            
            // Get the number of audio channels in the wav file so that we may allocate buffer space accordingly
            int numChannels = wavFileIn.getNumChannels();

            //Create input buffer covering whole song for easy access.
            double[] bufferIn = new double[(int)(numFramesIn * numChannels)];
            
            //Create output buffer for new song. [0][] is left channel; [1][] is right.
            double[][] bufferOut = new double[numChannels][(int)(numFramesOut)];
            
            // read frames from input file to bufferIn
            wavFileIn.readFrames(bufferIn, (int)numFramesIn);
            
            int rand = 0;
            for(int i = 0, j = 0; i < numFramesOut; i++, j++) 
            {              
               rand = randInt(0,9);
               if( j % numFramesHalfMeasure == 0 && j != 0) {
                  if(rand <= 4 && j % numFramesMeasure == 0) {
                     j-=numFramesMeasure;
                  }
                  else if(rand == 7) {
                     j-=numFramesQuarterMeasure;
                  }
                  else if(rand == 8) {
                     j-=numFramesMeasure;
                  }
                  else if(rand == 9) {
                     j-=numFramesHalfMeasure;
                  }
               }
               bufferOut[0][i] = bufferIn[2*(j) + numFramesSkip];
               bufferOut[1][i] = bufferIn[2*(j) + 1 + numFramesSkip];   
            }
            
            // write frames in bufferOut to our output file
            wavFileOut.writeFrames(bufferOut, (int)numFramesOut);
            
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
