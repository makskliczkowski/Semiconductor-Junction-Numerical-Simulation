using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Apka
{
    class Program
    {

        [STAThread]
        static void Main(string[] args)
        {

            Application.EnableVisualStyles();
            Application.Run(new CHART());

        }
    }
}
