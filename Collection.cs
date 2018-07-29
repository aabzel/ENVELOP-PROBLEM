using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication1
{
    class Collection
    {
        public int sizeOfCollection;
        public List<int> clabel;

        public Collection(int InSizeOfCollection) 
        {
            sizeOfCollection = InSizeOfCollection;
            clabel = new List<int>();
            clabel.Clear();
        }

        public void replenish_collection(Envelope Envlp) 
        {
            for (int i = 0; i < Envlp.elabel.Count(); i++)
            {
                if (!thereIsInTheCollection(Envlp.elabel[i]))
                { 
                    clabel.Add(Envlp.elabel[i]); 
                }
            }
        }

        private bool thereIsInTheCollection(int labeli) 
        {
            if (clabel.Contains(labeli)) 
            { 
                return true;
            }
            else 
            { 
                return false; 
            }
        }

        public void show() 
        {
            Console.Write("Collection: [ ");
            for (int i = 0; i < clabel.Count; i++)
            {
                Console.Write(" " + clabel[i] + " ");
            }
            Console.WriteLine("]");
        }

    }
}
