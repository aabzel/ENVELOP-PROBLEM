using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication1
{
    class Envelope
    {
        Random rnd = new Random();
        //hist of rand
        int maxNumberOfLabelsInEnvelope;
        int maxSizeOfCollection;
        public List<int> elabel; // stickers is a natural numbers


        public Envelope(int numberOfLabelsInEnvelope, int sizeOfCollection)
        {
            maxNumberOfLabelsInEnvelope = numberOfLabelsInEnvelope;
            maxSizeOfCollection = sizeOfCollection;
            elabel = new List<int>();
            elabel.Clear();
        }

        public int size()
        {
            return elabel.Count();
        }

        public void fill()
        {
            elabel.Clear();
            //Console.WriteLine("maxSizeOfCollection " + maxSizeOfCollection);
            int randomNumber;
            for (int i = 0; i < maxNumberOfLabelsInEnvelope; i++) 
            {
                randomNumber = rnd.Next(1, maxSizeOfCollection+1);
                //Console.Write("rand value " + randomNumber+"\n");
                elabel.Add(randomNumber);
    	    }
            //Console.WriteLine("");
        }

        public void show() 
        {
            Console.Write("Envelop:    [ ");
            for (int i=0; i < elabel.Count ; i++)
            {
                Console.Write(" " + elabel[i]+ " ");
            }
            Console.WriteLine("]");
        }
    }
}