using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace WebService
{
    internal class Program
    {
        static Random rnd = new Random();
        static void Main(string[] args)
        {

            Stopwatch watchLinear = Stopwatch.StartNew();
            int carId = BookCar();
            int hotelId = BookHotel();
            int planeId = BookPlane();
            Console.WriteLine($"Finished in {watchLinear.ElapsedMilliseconds/1000} second.");


            Stopwatch watchParallel = Stopwatch.StartNew();
            Task<int> carTask = Task.Factory.StartNew<int>(BookCar);
            Task<int> hotelTask = Task.Factory.StartNew<int>(BookHotel);
            Task<int> planeTask = Task.Factory.StartNew<int>(BookPlane);
            Task.WaitAll(carTask,hotelTask,planeTask);
            Console.WriteLine($"Finished in {watchParallel.ElapsedMilliseconds / 1000} second.");

            Console.ReadKey();
        }

        private static int BookPlane()
        {
            Console.WriteLine("Booking plane....");
            Thread.Sleep(5000);
            Console.WriteLine("The plane is booked!");
            return rnd.Next(100);
        }

        private static int BookHotel()
        {
            Console.WriteLine("Booking hotel....");
            Thread.Sleep(5000);
            Console.WriteLine("The hotel is booked!");
            return rnd.Next(100);
        }

        private static int BookCar()
        {
            Console.WriteLine("Booking car....");
            Thread.Sleep(5000);
            Console.WriteLine("The car is booked!");
            return rnd.Next(100);
        }
    }
}
