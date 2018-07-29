using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Speech.Synthesis;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            //Envelope envrlop = new Envelope(5, 5);
            int numberOfLabelsInSet = 5;
            int numberOfLabelsInEnvelope = 5;
            int numberOfExperiments = 100;
            int sizeOfHist = 100;

            Console.WriteLine("numberOfLabelsInSet: " + numberOfLabelsInSet);
            Console.WriteLine("numberOfLabelsInEnvelope: " + numberOfLabelsInEnvelope);
            Console.WriteLine("numberOfExperiments: " + numberOfExperiments);

            Lottery Lott = new Lottery(numberOfLabelsInSet, 
                                       numberOfLabelsInEnvelope, 
                                       sizeOfHist);

            for(int i=0; i<numberOfExperiments; i++)
            {
                Lott.carry_out_experiment();
	        }

            Lott.print_bar_chart();


        }
    }
}
