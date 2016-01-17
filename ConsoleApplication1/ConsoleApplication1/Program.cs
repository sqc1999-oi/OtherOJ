using System;
using System.IO;
using System.Security.Cryptography;
using static System.Console;

namespace ConsoleApplication1
{
	class Program
	{
		static void Main(string[] args)
		{
			if (args.Length < 1 || !File.Exists(args[0])) return;
			var md5 = MD5.Create();
			var hash = md5.ComputeHash(new FileStream(args[0], FileMode.Open));
			foreach (var i in hash) Write(i.ToString("x2"));
			WriteLine();
		}
	}
}
