using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime;
using System.Globalization;
using System.Text;
using System.Windows.Forms.DataVisualization.Charting;



namespace Apka
{


    public partial class CHART : Form
    {
       

        public CHART()
        {
            InitializeComponent();
        }

        private void STATISTICS_Click(object sender, EventArgs e)
        {
            stat1.BringToFront();
        }

        private void GRAPH_Click(object sender, EventArgs e)
        {
            charty3.BringToFront();
        }

        private void ABOUT_Click(object sender, EventArgs e)
        {
            abouty1.BringToFront();
        }
        private void sendToSchroedingerParameters()
        {
            /*
            0) x1
            1) y1
            2) x2
            3) y2
            4) x3
            5) y3
            6) bool include strain
            7) substrate ?
            8)Substratefinish
            9)T
            10)FirstMaterial_finish_point
            11)SecondMaterial_finish_point
            12)width
            */
            string x1, y1, x2, y2, x3, y3, T, subFinish, FirstFinish, SecondFinish, width;
            string includeStrain;
            string substrate;
            x1 = Convert.ToString(x1_change.Value);
            x2 = Convert.ToString(x2_change.Value);
            x3 = Convert.ToString(x3_change.Value);
            y1 = Convert.ToString(y1_change.Value);
            y2 = Convert.ToString(y2_change.Value);
            y3 = Convert.ToString(y3_change.Value);
            T = Convert.ToString(temp_change.Value);
            FirstFinish = Convert.ToString(width1updown.Value);
            SecondFinish = Convert.ToString(width2updown.Value);
            subFinish = Convert.ToString((width1updown.Value+width2updown.Value+ width3updown.Value)/10);
            width = Convert.ToString((width1updown.Value + width2updown.Value + width3updown.Value) + (width1updown.Value + width2updown.Value + width3updown.Value) / 5);
            includeStrain = Convert.ToString(Convert.ToInt32(check_strain.Checked));
            substrate = what_substrate.Text;
            string[] argv = new string [13];
            argv[0] = x1;
            argv[1] = y1;
            argv[2] = x2;
            argv[3] = y2;
            argv[4] = x3;
            argv[5] = y3;
            argv[6] = includeStrain;
            argv[7] = substrate;
            argv[8] = subFinish;
            argv[9] = T;
            argv[10] = FirstFinish;
            argv[11] = SecondFinish;
            argv[12] = width;
            stat1.setParametersForMaterials(argv);
        }
        //clicked calculation
        private void CALCULATE_Click(object sender, EventArgs e)
        {
            var format = new NumberFormatInfo();
            format.NegativeSign = "-";
            format.NumberDecimalSeparator = ".";

            //sendToSchroedingerParameters();
            //take parameters from textboxes
            //arguments:
            //1) PARABOLIC OR FOR MATERIALS
            /*if(MATERIALS)
            2) x1
            3) y1
            4) x2
            5) y2
            6) x3
            7) y3
            8) bool include strain
            9) substrate?
            10)eigenStatesNum
            11)stepInDiscretization
            12)DiscretizationPoints
            13) T
            14)Substratefinish
            15)FirstMaterial_finish_point
            16)SecondMaterial_finish_point
            17)width
            */
            string what = "MATERIALS";
            double x1, y1, x2, y2, x3, y3, T, step, firstFinish, secondFinish;
            string substrate;
            int includeStrain;
            int discretizationPoints, eigenstatesNum;
            double width, substrateFinish;

            x1 = Decimal.ToDouble(x1_change.Value);//2
            y1 = Decimal.ToDouble(y1_change.Value);//3
            x2 = Decimal.ToDouble(x2_change.Value);//4
            y2 = Decimal.ToDouble(y2_change.Value);//5
            x3 = Decimal.ToDouble(x3_change.Value);//6
            y3 = Decimal.ToDouble(y3_change.Value);//7
            includeStrain = Convert.ToInt32(check_strain.Checked);//8
            substrate = what_substrate.Text;//9
            eigenstatesNum = Decimal.ToInt32(eigStates_val.Value);//10
            step = Decimal.ToDouble(step_val.Value);//11
            substrateFinish = Convert.ToDouble(subWidth_val.Value, format);//13
            T = Decimal.ToDouble(temp_change.Value);//14
            firstFinish = Convert.ToDouble(width1updown.Value, format);//15
            secondFinish = Convert.ToDouble(width2updown.Value, format);//16
            width = Convert.ToDouble(width3updown.Value, format) + firstFinish + secondFinish + 2 * substrateFinish;//17
            discretizationPoints = Convert.ToInt32((width) / step);//12

            //====================================================EXE PROCESS-------------------------------------
            string cParams;
            cParams = what;//what
            cParams += " " + Convert.ToString(x1, System.Globalization.CultureInfo.InvariantCulture); //2
            cParams += " " + Convert.ToString(y1, System.Globalization.CultureInfo.InvariantCulture); //3
            cParams += " " + Convert.ToString(x2, System.Globalization.CultureInfo.InvariantCulture); //4
            cParams += " " + Convert.ToString(y2, System.Globalization.CultureInfo.InvariantCulture); //5
            cParams += " " + Convert.ToString(x3, System.Globalization.CultureInfo.InvariantCulture); //6
            cParams += " " + Convert.ToString(y3, System.Globalization.CultureInfo.InvariantCulture); //7
            cParams += " " + Convert.ToString(includeStrain, System.Globalization.CultureInfo.InvariantCulture); //8
            cParams += " " + Convert.ToString(substrate, System.Globalization.CultureInfo.InvariantCulture); //9
            cParams += " " + Convert.ToString(eigenstatesNum, System.Globalization.CultureInfo.InvariantCulture); //10
            cParams += " " + Convert.ToString(step, System.Globalization.CultureInfo.InvariantCulture); //11
            cParams += " " + Convert.ToString(discretizationPoints, System.Globalization.CultureInfo.InvariantCulture); //12
            cParams += " " + Convert.ToString(T, System.Globalization.CultureInfo.InvariantCulture); //13
            cParams += " " + Convert.ToString(substrateFinish, System.Globalization.CultureInfo.InvariantCulture); //14
            cParams += " " + Convert.ToString(firstFinish, System.Globalization.CultureInfo.InvariantCulture); //15
            cParams += " " + Convert.ToString(secondFinish, System.Globalization.CultureInfo.InvariantCulture); //16
            cParams += " " + Convert.ToString(width, System.Globalization.CultureInfo.InvariantCulture); //17


            var filePath = Path.Combine(Directory.GetCurrentDirectory(), "LasersAndMaterials.exe");
            var fileDat2 = Path.Combine(Directory.GetCurrentDirectory(), "GaInPAs.dat");//for secondmaterial
            var fileDat1 = Path.Combine(Directory.GetCurrentDirectory(), "AlGaAsSb.dat");//for first 
            var fileDat3 = Path.Combine(Directory.GetCurrentDirectory(), "substrate.dat"); //only substrate, make width as we want
            var fileDat4 = Path.Combine(Directory.GetCurrentDirectory(), "AlGaAsSb2.dat"); //for third material

            //exe process open
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = false;
            startInfo.UseShellExecute = false;
            startInfo.FileName = filePath;
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = cParams;
            try
            {

                using (Process exeProcess = Process.Start(startInfo))
                {
                    exeProcess.WaitForExit();
                }
                charty3.calculClicked(fileDat1, fileDat2, fileDat3,fileDat4, Decimal.ToDouble(width1updown.Value), Decimal.ToDouble(width2updown.Value), Decimal.ToDouble(width3updown.Value), substrateFinish, step, eigenstatesNum);
            }
            catch
            {
                MessageBox.Show("Couldn't calculate, try again", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

    }

    private void functionMenu_SelectedIndexChanged(object sender, EventArgs e)
    {

    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {

    }

    private void xi_Click(object sender, EventArgs e)
    {

    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {

    }

    private void xf_Click(object sender, EventArgs e)
    {

    }

    private void label1_Click(object sender, EventArgs e)
    {

    }

    private void textBox3_TextChanged(object sender, EventArgs e)
    {

    }

    private void label2_Click(object sender, EventArgs e)
    {

    }

    private void textBox4_TextChanged(object sender, EventArgs e)
    {

    }

    private void laRank_Click(object sender, EventArgs e)
    {

    }

    private void abouty1_Load(object sender, EventArgs e)
    {

    }

    private void numericUpDown2_ValueChanged(object sender, EventArgs e)
    {

    }

    private void CHART_Load(object sender, EventArgs e)
    {
        what_substrate.Text = "GaAs";
    }

    private void charty2_Load(object sender, EventArgs e)
    {

    }

    private void x2_change_ValueChanged(object sender, EventArgs e)
    {

    }
}
}
