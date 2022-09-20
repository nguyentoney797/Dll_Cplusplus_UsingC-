using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using OpenCvSharp;

namespace ConsoleApp1
{
    class Program
    {
        public const string ImageLabel = @"D:/Project/ProjectCustomer/TaiDoDo/ImageLabel/x64/Debug";
        [DllImport(@"ImageLabel.dll", CallingConvention = CallingConvention.Cdecl)] // 
        [System.Runtime.InteropServices.ComVisible(true)]
        public static extern void COLOR_SPACE(int[] single_layer, int[] ListColor, int startRow);

        static void Main(string[] args)
        {
            var d = new int[224*224];
            var l = new int[5*3];
            List<Point> a = new List<Point>();
            var out2= new Mat(500, 480, MatType.CV_8UC3);
            COLOR_SPACE(d, l, 0);
        }
    }
}
