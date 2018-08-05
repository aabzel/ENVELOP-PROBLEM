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
            int numberOfExperiments = 1000;
            int sizeOfHist = 100;

            Console.WriteLine("numberOfExperiments: " + numberOfExperiments);

            for (int numberOfLabelsInSet = 1; numberOfLabelsInSet < 20; numberOfLabelsInSet++)
            {
                for (int numberOfLabelsInEnvelope = 1; numberOfLabelsInEnvelope < 20; numberOfLabelsInEnvelope++)
                {
                    Console.WriteLine("numberOfLabelsInSet: " + numberOfLabelsInSet);
                    Console.WriteLine("numberOfLabelsInEnvelope: " + numberOfLabelsInEnvelope);
                    Lottery Lott = new Lottery(numberOfLabelsInSet,
                           numberOfLabelsInEnvelope,
                           sizeOfHist);

                    Lott.carry_out_experiments(numberOfExperiments);

                    Lott.print_bar_chart();

                }
            }
            //generate html table
        }
    }
}
