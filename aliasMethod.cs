using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Alias
{
    public class AliasMethod
    {
        /* The probability and alias tables. */
        private int[] _alias;
        private double[] _probability;

        public AliasMethod(List<Double> probabilities)
        {

            /* Allocate space for the probability and alias tables. */
            _probability = new double[probabilities.Count];
            _alias = new int[probabilities.Count];

            /* Compute the average probability and cache it for later use. */
            double average = 1.0 / probabilities.Count;

            /* Create two stacks to act as worklists as we populate the tables. */
            var small = new Stack<int>();
            var large = new Stack<int>();

            /* Populate the stacks with the input probabilities. */
            for (int i = 0; i < probabilities.Count; ++i)
            {
                /* If the probability is below the average probability, then we add
                 * it to the small list; otherwise we add it to the large list.
                 */
                if (probabilities[i] >= average)
                    large.Push(i);
                else
                    small.Push(i);
            }

            /* As a note: in the mathematical specification of the algorithm, we
             * will always exhaust the small list before the big list.  However,
             * due to floating point inaccuracies, this is not necessarily true.
             * Consequently, this inner loop (which tries to pair small and large
             * elements) will have to check that both lists aren't empty.
             */
            while (small.Count > 0 && large.Count > 0)
            {
                /* Get the index of the small and the large probabilities. */
                int less = small.Pop();
                int more = large.Pop();

                /* These probabilities have not yet been scaled up to be such that
                 * 1/n is given weight 1.0.  We do this here instead.
                 */
                _probability[less] = probabilities[less] * probabilities.Count;
                _alias[less] = more;

                /* Decrease the probability of the larger one by the appropriate
                 * amount.
                 */
                probabilities[more] = (probabilities[more] + probabilities[less] - average);

                /* If the new probability is less than the average, add it into the
                 * small list; otherwise add it to the large list.
                 */
                if (probabilities[more] >= average)
                    large.Push(more);
                else
                    small.Push(more);
            }

            /* At this point, everything is in one list, which means that the
             * remaining probabilities should all be 1/n.  Based on this, set them
             * appropriately.  Due to numerical issues, we can't be sure which
             * stack will hold the entries, so we empty both.
             */
            while (small.Count > 0)
                _probability[small.Pop()] = 1.0;
            while (large.Count > 0)
                _probability[large.Pop()] = 1.0;
        }

        /**
         * Samples a value from the underlying distribution.
         *
         * @return A random value sampled from the underlying distribution.
         */
        public int next()
        {

            long tick = DateTime.Now.Ticks;
            var seed = ((int)(tick & 0xffffffffL) | (int)(tick >> 32));
            unchecked
            {
                seed = (seed + Guid.NewGuid().GetHashCode() + new Random().Next(0, 100));
            }
            var random = new Random(seed);
            int column = random.Next(_probability.Length);

            /* Generate a biased coin toss to determine which option to pick. */
            bool coinToss = random.NextDouble() < _probability[column];

            return coinToss ? column : _alias[column];
        }
    }
}
