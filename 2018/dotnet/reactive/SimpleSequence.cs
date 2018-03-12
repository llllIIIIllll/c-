using System;
using System.Collections.Generic;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using System.Threading;

namespace reactive
{
    class SimpleSequence
    {
        public static void TestSimpleSequence()
        {
            IObservable<int> source = Observable.Range(1, 10);
            IDisposable subscription = source.Subscribe(
                x => Console.WriteLine("OnNext: {0}", x),
                ex => Console.WriteLine("OnError: {0}", ex.Message),
                () => Console.WriteLine("OnComplete"));
            Console.WriteLine("Press ENTER to unsubscribe...");
            Console.ReadLine();
            subscription.Dispose();
        }

        public static void Timer()
        {
            Console.WriteLine("Current Time: " + DateTime.Now);
            var source = Observable.Timer(TimeSpan.FromSeconds(5), TimeSpan.FromSeconds(10))
                .Timestamp();
            using (source.Subscribe(x => Console.WriteLine("{0}: {1}", x.Value, x.Timestamp)))
            {
                Console.WriteLine("Press any key to unsubscribe");
                Console.ReadKey();
            }
            Console.WriteLine("Press any key to exit");
            Console.ReadKey();
        }

        public static void Collection()
        {
            IEnumerable<int> e = new List<int> { 1, 2, 3, 4, 5 };
            IObservable<int> source = e.ToObservable();
            IDisposable subscription = source.Subscribe(
                x => Console.WriteLine("OnNext: {0}", x),
                ex => Console.WriteLine("OnError: {0}", ex.Message),
                () => Console.WriteLine("OnCompleted"));
            Console.ReadKey();
        }

        public static void ColdHot()
        {
            IObservable<long> source = Observable.Interval(TimeSpan.FromSeconds(1));

            IDisposable subscription1 = source.Subscribe(
                x => Console.WriteLine("Observer 1: OnNext: {0}", x),
                ex => Console.WriteLine("Observer 1: OnError: {0}", ex.Message),
                () => Console.WriteLine("Observer 1: OnCompleted: "));

            IDisposable subscription2 = source.Subscribe(
                x => Console.WriteLine("Observer 2: OnNext: {0}", x),
                ex => Console.WriteLine("Observer 2: OnError: {0}", ex.Message),
                () => Console.WriteLine("Observer 2: OnCompleted: "));

            Console.WriteLine("Press any key to unsubscribe");
            Console.ReadLine();
            subscription1.Dispose();
            subscription2.Dispose();
        }

        public static void Test()
        {
            Console.WriteLine("Current Time: " + DateTime.Now);
            var source = Observable.Interval(TimeSpan.FromSeconds(1));            //creates a sequence

            IConnectableObservable<long> hot = Observable.Publish<long>(source);  // convert the sequence into a hot sequence

            IDisposable subscription1 = hot.Subscribe(                        // no value is pushed to 1st subscription at this point
                                        x => Console.WriteLine("Observer 1: OnNext: {0}", x),
                                        ex => Console.WriteLine("Observer 1: OnError: {0}", ex.Message),
                                        () => Console.WriteLine("Observer 1: OnCompleted"));
            Console.WriteLine("Current Time after 1st subscription: " + DateTime.Now);
            Thread.Sleep(3000);  //idle for 3 seconds
            hot.Connect();       // hot is connected to source and starts pushing value to subscribers 
            Console.WriteLine("Current Time after Connect: " + DateTime.Now);
            Thread.Sleep(3000);  //idle for 3 seconds
            Console.WriteLine("Current Time just before 2nd subscription: " + DateTime.Now);

            IDisposable subscription2 = hot.Subscribe(     // value will immediately be pushed to 2nd subscription
                                        x => Console.WriteLine("Observer 2: OnNext: {0}", x),
                                        ex => Console.WriteLine("Observer 2: OnError: {0}", ex.Message),
                                        () => Console.WriteLine("Observer 2: OnCompleted"));
            Console.ReadKey();
        }
    }
}
