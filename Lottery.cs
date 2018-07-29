using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace ConsoleApplication1
{
    class Lottery
    {
        int numOfPurchasedEnvelopes;
        int sizeOfBarChart;
        public List<int> bar_chart;

        Collection MyColl;
        Envelope Envl;
        int average_amout_of_envelops;

        public Lottery(int numberOfLabelsInSet, 
                       int numberOfLabelsInEnvelope,
                       int inSizeOfBarChart) 
        {
            average_amout_of_envelops = 0;
            sizeOfBarChart = inSizeOfBarChart;

            bar_chart = new List<int>();
            for (int i = 1; i <= sizeOfBarChart; i++)
            {
                bar_chart.Add(0);
            }

            numOfPurchasedEnvelopes = 0;
            MyColl = new Collection(numberOfLabelsInSet);
            Envl = new Envelope(numberOfLabelsInEnvelope, 
                                numberOfLabelsInSet);
        }

        public int carry_out_experiment()
        {
            numOfPurchasedEnvelopes = 0;
            MyColl.clabel.Clear();
            while (MyColl.clabel.Count() < MyColl.sizeOfCollection)
            {
                numOfPurchasedEnvelopes++;
		        Envl.fill();
                //Envl.show();
                MyColl.replenish_collection(Envl);
		        //MyColl.show();   
		        Envl.elabel.Clear();
                //Console.WriteLine("");
	        }

            //Console.WriteLine("numOfPurchasedEnvelopes: " + numOfPurchasedEnvelopes);

            if (numOfPurchasedEnvelopes < bar_chart.Count)
            {
                bar_chart[numOfPurchasedEnvelopes]++;
            }
            else 
            {
                Console.WriteLine("bar_chart overflow!");
                Console.WriteLine("numOfPurchasedEnvelopes:" + numOfPurchasedEnvelopes);
            }
            MyColl.clabel.Clear();
            return numOfPurchasedEnvelopes; 
        }

        public void print_bar_chart() 
        {
            Console.WriteLine("\n Result of modeling: (number of bought envelops: frequency of matches)");
            for (int i = 0; i < bar_chart.Count; i++ )
            {
                if (0 < bar_chart[i]) 
                {
                    Console.WriteLine(i + ": " + bar_chart[i]);
                }

            }
            find_average_amout_of_envelops();
            Console.WriteLine("average_amout_of_envelops: " + average_amout_of_envelops);

        }
        int find_average_amout_of_envelops() 
        {
            average_amout_of_envelops = 0;
	        int maxElelent = 0;
	        int indmaxEl = 0;

            for(int s=0; s<bar_chart.Count; s++) {
		        if(bar_chart[s]>maxElelent) {
                    maxElelent = bar_chart[s];
			        indmaxEl = s;
		        }
	        }
            average_amout_of_envelops = indmaxEl;
            return indmaxEl;
        }
    }
}
