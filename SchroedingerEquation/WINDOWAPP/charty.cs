using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime;
using System.Globalization;
using System.Text;
using System.Windows.Forms.DataVisualization.Charting;
using System.Runtime.CompilerServices;

namespace Apka
{
 

    public partial class charty : UserControl
    {



        public charty()
        {
            InitializeComponent();
            materialBox.Text = "AlGaAsSb";
        }
        public void calculClicked(string fileDat1, string fileDat2, string fileDat3, string fileDat4, double width1, double width2, double width3, double subWidth, double step, int eigNum)
        {
            var format = new NumberFormatInfo();
            format.NegativeSign = "-";
            format.NumberDecimalSeparator = ".";
            double width = width1 + width2 + width3 + 2 * subWidth;
            int discretizationPoints = Convert.ToInt32(width / step);
            //========================================ADDING PLOTS============================================================================================================================================================
            //clearing points

            foreach (var series in chart_extremas.Series)
            {
                series.Points.Clear();
            }
            foreach (var series in chart_masses.Series)
            {
                series.Points.Clear();
            }
            ENERGYCHART.Series.Clear();
            for (int i = 0; i < eigNum; i++)
            {
                ENERGYCHART.Series.Add("CondWave" + Convert.ToString(i, format));//adding series to the chart!!!  //wavefunctions
                ENERGYCHART.Series["CondWave" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
                ENERGYCHART.Series.Add("EnergyCond" + Convert.ToString(i, format));//adding series to the chart!!! conduction band energy
                ENERGYCHART.Series["EnergyCond" + Convert.ToString(i, format)].ChartType = SeriesChartType.StepLine;
                ENERGYCHART.Series.Add("EnergyVal" + Convert.ToString(i, format));//adding series to the chart!!! valence band energy
                ENERGYCHART.Series["EnergyVal" + Convert.ToString(i, format)].ChartType = SeriesChartType.StepLine;
                ENERGYCHART.Series.Add("ValWave" + Convert.ToString(i, format));//adding series to the chart!!! valence wavefunctions
                ENERGYCHART.Series["ValWave" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
                //---------------------------POTENTIALS----------------------------------
                ENERGYCHART.Series.Add("Ev_hh");
                ENERGYCHART.Series["Ev_hh"].ChartType = SeriesChartType.StepLine;
                ENERGYCHART.Series.Add("Ev_lh");
                ENERGYCHART.Series["Ev_lh"].ChartType = SeriesChartType.StepLine;
                ENERGYCHART.Series.Add("Ev_so");
                ENERGYCHART.Series["Ev_so"].ChartType = SeriesChartType.StepLine;
                ENERGYCHART.Series.Add("Ec");
                ENERGYCHART.Series["Ec"].ChartType = SeriesChartType.StepLine;
            }
            ChartArea CA = ENERGYCHART.ChartAreas[0];  // quick reference
            CA.AxisX.ScaleView.Zoomable = true;
            CA.CursorX.AutoScroll = true;
            CA.CursorX.IsUserSelectionEnabled = true;
            ENERGYCHART.ChartAreas[0].AxisX.LabelStyle.Format = "0.0";
            CA.AxisX.Minimum = 0.0;
            CA.AxisX.Interval = 80;



            //reading from files for numerical calc
            //=-----------------------------------------FOR DRAWING GRAPHS------------------------------------------------------------------------------------------------------------------------------------------------------------
            string[] energiesCond = new string[eigNum];
            string[] energiesVal = new string[eigNum];
            string[,] wavefunctionsVal = new string[eigNum, discretizationPoints];
            string[,] wavefunctionsCond = new string[eigNum, discretizationPoints];
            ///-------reading energies and wavefunctions----------------------------------------------------------------------------------------
            //valence----------------------------------------------------------------------
            using (StreamReader sr = new StreamReader("energiesVal.dat"))
            {
                string line;
                int counter = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    energiesVal[counter] = line;
                    counter++;
                }
                sr.Close();
            }

            using (StreamReader sr = new StreamReader("wavefunctionsVal.dat"))
            {
                string line;
                int counter = 0;

                while ((line = sr.ReadLine()) != null)
                {
                    var array = line.Split(new string[] { "\t\t" }, StringSplitOptions.RemoveEmptyEntries);
                    for (int i = 1; i <= eigNum; i++)
                    {
                        wavefunctionsVal[i - 1, counter] = array[i];
                    }
                    counter++;
                }
                sr.Close();
            }
            //conduction------------------------------------------------------------------
            using (StreamReader sr = new StreamReader("energiesCond.dat"))
            {
                string line;
                int counter = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    energiesCond[counter] = line;
                    counter++;
                }
                sr.Close();
            }

            using (StreamReader sr = new StreamReader("wavefunctionsCond.dat"))
            {
                string line;
                int counter = 0;

                while ((line = sr.ReadLine()) != null)
                {
                    var array = line.Split(new string[] { "\t\t" }, StringSplitOptions.RemoveEmptyEntries);
                    for (int i = 1; i <= eigNum; i++)
                    {
                        wavefunctionsCond[i - 1, counter] = array[i];
                    }
                    counter++;
                }
                sr.Close();
            }
            //----------------------------------------------------------------------------------------------------------------------------------------------------------------
            ///-------------------------------------parameters for potentials READING AND WRITING TO FILES---------------------------------------------------------------------
            //substrate
            string m_eff_sub, Ev_hh_sub, Ev_lh_sub, Ev_so_sub, Ec_sub, Eg_sub;
            m_eff_sub = Ev_hh_sub = Ev_lh_sub = Ev_so_sub = Ec_sub = "0";
            //1 & 3
            string m_eff_1, Ev_hh_1, Ev_lh_1, Ev_so_1, Ec_1, Eg_1;
            m_eff_1 = Ev_hh_1 = Ev_lh_1 = Ev_so_1 = Ec_1  = "0";
            //2
            string m_eff_2, Ev_hh_2, Ev_lh_2, Ev_so_2, Ec_2, Eg_2;
            m_eff_2 = Ev_hh_2 = Ev_lh_2 = Ev_so_2 = Ec_2 = "0";
            //3
            string m_eff_3, Ev_hh_3, Ev_lh_3, Ev_so_3, Ec_3, Eg_3;
            m_eff_3 = Ev_hh_3 = Ev_lh_3 = Ev_so_3 = Ec_3= "0";
            //fileDat1 -- 1 material: has x and y, skip them at the beggining!
            using (StreamReader sr = new StreamReader(fileDat1))
            {
                string line;
                int counter = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    if (counter == 1)
                    {
                        var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                        m_eff_1 = array[2];
                        Ev_hh_1 = array[3];
                        Ev_lh_1 = array[4];
                        Ev_so_1 = array[5];
                        Ec_1 = array[6];
                        Eg_1 = array[7];
                    }
                    if (counter != 1) counter++;

                }
                sr.Close();
            }
            //fileDat2 -- 2 material also has x & y!!!
            using (StreamReader sr = new StreamReader(fileDat2))
            {
                string line;
                int counter = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    if (counter == 1)
                    {
                        var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                        m_eff_2 = array[2];
                        Ev_hh_2 = array[3];
                        Ev_lh_2 = array[4];
                        Ev_so_2 = array[5];
                        Ec_2 = array[6];
                        Eg_2 = array[7];
                    }
                    if (counter != 1) counter++;

                }
                sr.Close();
            }
            //fileDat3 doesn't have x y!!!!
            using (StreamReader sr = new StreamReader(fileDat3))
            {
                string line;
                int counter = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    if (counter == 1)
                    {
                        var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                        m_eff_sub = array[0];
                        Ev_hh_sub = array[1];
                        Ev_lh_sub = array[2];
                        Ev_so_sub = array[3];
                        Ec_sub = array[4];
                        Eg_sub = array[5];
                    }
                    if (counter != 1) counter++;

                }
                sr.Close();
            }
            //fileDat4 has x y!!!!
            using (StreamReader sr = new StreamReader(fileDat4))
            {
                string line;
                int counter = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    if (counter == 1)
                    {
                        var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                        m_eff_3 = array[2];
                        Ev_hh_3 = array[3];
                        Ev_lh_3 = array[4];
                        Ev_so_3 = array[5];
                        Ec_3 = array[6];
                        Eg_3 = array[7];
                    }
                    if (counter != 1) counter++;

                }
                sr.Close();
            }
            //===========================================================================adding points to charts================================================================================
            double EvalMax = Convert.ToDouble(energiesVal[eigNum - 1], format);
            double EcondMin = Convert.ToDouble(energiesCond[0], format);
            double Eg = EcondMin - EvalMax;
            Eg_printer.Text = "Eg = " + Convert.ToString(Eg) + "eV";
            using (StreamReader sr = new StreamReader("overlapping.dat"))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    Overlapping_printer.Text = "Overlapping = " + line;
                }
            }
            //MessageBox.Show("The band gap is" + Convert.ToString(EcondMin - EvalMax), "LOOK", MessageBoxButtons.OK, MessageBoxIcon.Information);
            int k = 0; //for positions in arrays


            //substrate-------------------------------------------------------------------------------
            int N; //number of steps for each
            double subwidth = subWidth;
            N = Convert.ToInt32(subwidth / step);
            double where_width = 0;
            double stepper = where_width;
            using (StreamWriter outputFile = new StreamWriter("toPlot.dat"))
            {
                string lineForPlot;
                //x[nm] WaveVal WaveCond  Vhh Vlh Vso Vc Ev Ec 
                for (int i = 0; i < N; i++)
                {
                    
                    //------------------------POTENTIALS-------------------------------------------
                    ENERGYCHART.Series["Ev_hh"].Points.AddXY(stepper, Convert.ToDouble(Ev_hh_sub, format));
                    ENERGYCHART.Series["Ev_lh"].Points.AddXY(stepper, Convert.ToDouble(Ev_lh_sub, format));
                    ENERGYCHART.Series["Ev_so"].Points.AddXY(stepper, Convert.ToDouble(Ev_so_sub, format));
                    ENERGYCHART.Series["Ec"].Points.AddXY(stepper, Convert.ToDouble(Ec_sub, format));
                    string Vhh = Ev_hh_sub;
                    string Vlh = Ev_lh_sub;
                    string Vso = Ev_so_sub;
                    string Vc = Ec_sub;

                    //------------------------THE REST --------------------------------------------
                    for (int j = 0; j < eigNum; j++)
                    {
                        double enCond = Convert.ToDouble(energiesCond[j], format);
                        double enVal = Convert.ToDouble(energiesVal[j], format);
                        ENERGYCHART.Series["EnergyCond" + Convert.ToString(j)].Points.AddXY(stepper, enCond);
                        ENERGYCHART.Series["EnergyVal" + Convert.ToString(j)].Points.AddXY(stepper, enVal);
                        double movedEigFunCond = Double.Parse(wavefunctionsCond[j, k], format) + enCond;
                        double movedEigFunVal = Double.Parse(wavefunctionsVal[j, k], format) + enVal;
                        ENERGYCHART.Series["CondWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunCond);// plot the functions at the level of corresponding energies
                        ENERGYCHART.Series["ValWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunVal);// plot the functions at the level of corresponding energies
                        lineForPlot = Convert.ToString(stepper / 10, format) + " " + movedEigFunVal.ToString(format) + " " + movedEigFunCond.ToString(format) + " " + Vhh + " " + Vlh + " " + Vso + " " + Vc;
                        outputFile.WriteLine(lineForPlot);
                    }
                    stepper += step;
                    k++;
                }
                //material1-------------------------------------------------------------
                where_width += subwidth;
                stepper = where_width;
                N = Convert.ToInt32(width1 / step);
                for (int i = 0; i < N; i++)
                {
                    //------------------------POTENTIALS-------------------------------------------
                    ENERGYCHART.Series["Ev_hh"].Points.AddXY(stepper, Convert.ToDouble(Ev_hh_1, format));
                    ENERGYCHART.Series["Ev_lh"].Points.AddXY(stepper, Convert.ToDouble(Ev_lh_1, format));
                    ENERGYCHART.Series["Ev_so"].Points.AddXY(stepper, Convert.ToDouble(Ev_so_1, format));
                    ENERGYCHART.Series["Ec"].Points.AddXY(stepper, Convert.ToDouble(Ec_1, format));
                    string Vhh = Ev_hh_1;
                    string Vlh = Ev_lh_1;
                    string Vso = Ev_so_1;
                    string Vc = Ec_1;
                    //------------------------THE REST --------------------------------------------
                    for (int j = 0; j < eigNum; j++)
                    {
                        double enCond = Convert.ToDouble(energiesCond[j], format);
                        double enVal = Convert.ToDouble(energiesVal[j], format);
                        ENERGYCHART.Series["EnergyCond" + Convert.ToString(j)].Points.AddXY(stepper, enCond);
                        ENERGYCHART.Series["EnergyVal" + Convert.ToString(j)].Points.AddXY(stepper, enVal);
                        double movedEigFunCond = Double.Parse(wavefunctionsCond[j, k], format) + enCond;
                        double movedEigFunVal = Double.Parse(wavefunctionsVal[j, k], format) + enVal;
                        ENERGYCHART.Series["CondWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunCond);// plot the functions at the level of corresponding energies
                        ENERGYCHART.Series["ValWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunVal);// plot the functions at the level of corresponding energies
                        lineForPlot = Convert.ToString(stepper / 10, format) + " " + movedEigFunVal.ToString(format) + " " + movedEigFunCond.ToString(format) + " " + Vhh + " " + Vlh + " " + Vso + " " + Vc;
                        outputFile.WriteLine(lineForPlot);
                    }
                    stepper += step;
                    k++;
                }
                //material2----------------------------------------------------------
                where_width += width1;
                stepper = where_width;
                N = Convert.ToInt32(width2 / step);
                for (int i = 0; i < N; i++)
                {
                    //------------------------POTENTIALS-------------------------------------------
                    ENERGYCHART.Series["Ev_hh"].Points.AddXY(stepper, Convert.ToDouble(Ev_hh_2, format));
                    ENERGYCHART.Series["Ev_lh"].Points.AddXY(stepper, Convert.ToDouble(Ev_lh_2, format));
                    ENERGYCHART.Series["Ev_so"].Points.AddXY(stepper, Convert.ToDouble(Ev_so_2, format));
                    ENERGYCHART.Series["Ec"].Points.AddXY(stepper, Convert.ToDouble(Ec_2, format));
                    string Vhh = Ev_hh_2;
                    string Vlh = Ev_lh_2;
                    string Vso = Ev_so_2;
                    string Vc = Ec_2;
                    //------------------------THE REST --------------------------------------------
                    for (int j = 0; j < eigNum; j++)
                    {
                        double enCond = Convert.ToDouble(energiesCond[j], format);
                        double enVal = Convert.ToDouble(energiesVal[j], format);
                        ENERGYCHART.Series["EnergyCond" + Convert.ToString(j)].Points.AddXY(stepper, enCond);
                        ENERGYCHART.Series["EnergyVal" + Convert.ToString(j)].Points.AddXY(stepper, enVal);
                        double movedEigFunCond = Double.Parse(wavefunctionsCond[j, k], format) + enCond;
                        double movedEigFunVal = Double.Parse(wavefunctionsVal[j, k], format) + enVal;
                        ENERGYCHART.Series["CondWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunCond);// plot the functions at the level of corresponding energies
                        ENERGYCHART.Series["ValWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunVal);// plot the functions at the level of corresponding energies
                        lineForPlot = Convert.ToString(stepper / 10, format) + " " + movedEigFunVal.ToString(format) + " " + movedEigFunCond.ToString(format) + " " + Vhh + " " + Vlh + " " + Vso + " " + Vc;
                        outputFile.WriteLine(lineForPlot);
                    }
                    stepper += step;
                    k++;
                }
                //material3--------------------------------------------------------
                where_width += width2;
                stepper = where_width;
                N = Convert.ToInt32(width3 / step);
                for (int i = 0; i < N; i++)
                {
                    //------------------------POTENTIALS-------------------------------------------
                    ENERGYCHART.Series["Ev_hh"].Points.AddXY(stepper, Convert.ToDouble(Ev_hh_3, format));
                    ENERGYCHART.Series["Ev_lh"].Points.AddXY(stepper, Convert.ToDouble(Ev_lh_3, format));
                    ENERGYCHART.Series["Ev_so"].Points.AddXY(stepper, Convert.ToDouble(Ev_so_3, format));
                    ENERGYCHART.Series["Ec"].Points.AddXY(stepper, Convert.ToDouble(Ec_3, format));
                    string Vhh = Ev_hh_3;
                    string Vlh = Ev_lh_3;
                    string Vso = Ev_so_3;
                    string Vc = Ec_3;
                    //------------------------THE REST --------------------------------------------
                    for (int j = 0; j < eigNum; j++)
                    {
                        double enCond = Convert.ToDouble(energiesCond[j], format);
                        double enVal = Convert.ToDouble(energiesVal[j], format);
                        ENERGYCHART.Series["EnergyCond" + Convert.ToString(j)].Points.AddXY(stepper, enCond);
                        ENERGYCHART.Series["EnergyVal" + Convert.ToString(j)].Points.AddXY(stepper, enVal);
                        double movedEigFunCond = Double.Parse(wavefunctionsCond[j, k], format) + enCond;
                        double movedEigFunVal = Double.Parse(wavefunctionsVal[j, k], format) + enVal;
                        ENERGYCHART.Series["CondWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunCond);// plot the functions at the level of corresponding energies
                        ENERGYCHART.Series["ValWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunVal);// plot the functions at the level of corresponding energies
                        lineForPlot = Convert.ToString(stepper / 10, format) + " " + movedEigFunVal.ToString(format) + " " + movedEigFunCond.ToString(format) + " " + Vhh + " " + Vlh + " " + Vso + " " + Vc;
                        outputFile.WriteLine(lineForPlot);
                    }
                    stepper += step;
                    k++;
                }
                //substrate again--------------------------------------------------------
                where_width += width3;
                stepper = where_width;
                N = Convert.ToInt32(subwidth / step);
                for (int i = 0; i < N; i++)
                {
                    //------------------------POTENTIALS-------------------------------------------
                    ENERGYCHART.Series["Ev_hh"].Points.AddXY(stepper, Convert.ToDouble(Ev_hh_sub, format));
                    ENERGYCHART.Series["Ev_lh"].Points.AddXY(stepper, Convert.ToDouble(Ev_lh_sub, format));
                    ENERGYCHART.Series["Ev_so"].Points.AddXY(stepper, Convert.ToDouble(Ev_so_sub, format));
                    ENERGYCHART.Series["Ec"].Points.AddXY(stepper, Convert.ToDouble(Ec_sub, format));
                    string Vhh = Ev_hh_sub;
                    string Vlh = Ev_lh_sub;
                    string Vso = Ev_so_sub;
                    string Vc = Ec_sub;
                    //------------------------THE REST --------------------------------------------
                    for (int j = 0; j < eigNum; j++)
                    {
                        double enCond = Convert.ToDouble(energiesCond[j], format);
                        double enVal = Convert.ToDouble(energiesVal[j], format);
                        ENERGYCHART.Series["EnergyCond" + Convert.ToString(j)].Points.AddXY(stepper, enCond);
                        ENERGYCHART.Series["EnergyVal" + Convert.ToString(j)].Points.AddXY(stepper, enVal);
                        double movedEigFunCond = Double.Parse(wavefunctionsCond[j, k], format) + enCond;
                        double movedEigFunVal = Double.Parse(wavefunctionsVal[j, k], format) + enVal;
                        ENERGYCHART.Series["CondWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunCond);// plot the functions at the level of corresponding energies
                        ENERGYCHART.Series["ValWave" + Convert.ToString(j, format)].Points.AddXY(stepper, movedEigFunVal);// plot the functions at the level of corresponding energies
                        lineForPlot = Convert.ToString(stepper / 10, format) + " " + movedEigFunVal.ToString(format) + " " + movedEigFunCond.ToString(format) + " " + Vhh + " " + Vlh + " " + Vso + " " + Vc;
                        outputFile.WriteLine(lineForPlot);
                    }
                    stepper += step;
                    k++;
                }
            }
            //=============================================================================================interpolation-===============================================================================================
            if (materialBox.Text == "AlGaAsSb")
            {
                using (StreamReader sr = new StreamReader(Path.Combine(Directory.GetCurrentDirectory(), "AlGaAsSb_Interp.dat")))
                {
                    string line;
                    int counter = 0;
                    while ((line = sr.ReadLine()) != null)
                    {
                        if (counter == 1)
                        {
                            var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                            string x = array[0];
                            string m_eff = array[2];
                            string Ev_hh = array[3];
                            string Ev_lh = array[4];
                            string Ev_so = array[5];
                            string Ec = array[6];
                            chart_masses.Series["m_eff"].Points.AddXY(x, m_eff);
                            chart_extremas.Series["Ev_hh"].Points.AddXY(x, Ev_hh);
                            chart_extremas.Series["Ev_lh"].Points.AddXY(x, Ev_lh);
                            chart_extremas.Series["Ev_so"].Points.AddXY(x, Ev_so);
                            chart_extremas.Series["Ec"].Points.AddXY(x, Ec);
                        }
                        if (counter != 1) counter++;

                    }
                    sr.Close();
                }
            }
            else if(materialBox.Text == "GaInPAs")
            {
                using (StreamReader sr = new StreamReader(Path.Combine(Directory.GetCurrentDirectory(), "GaInPAs_Interp.dat")))
                {
                    string line;
                    int counter = 0;
                    while ((line = sr.ReadLine()) != null)
                    {
                        if (counter == 1)
                        {
                            var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                            chart_masses.Series["m_eff"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[2]));
                            chart_extremas.Series["Ev_hh"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[3]));
                            chart_extremas.Series["Ev_lh"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[4]));
                            chart_extremas.Series["Ev_so"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[5]));
                            chart_extremas.Series["Ec"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[6]));
                        }
                        if (counter != 1) counter++;

                    }
                    sr.Close();
                }
            }
        }
        private void NUM_Click(object sender, EventArgs e)
        {

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void charty_Load(object sender, EventArgs e)
        {

        }

        private void tableLayout_Paint(object sender, PaintEventArgs e)
        {

        }

        private void materialBox_SelectedValueChanged(object sender, EventArgs e)
        {
            foreach (var series in chart_extremas.Series)
            {
                series.Points.Clear();
            }
            foreach (var series in chart_masses.Series)
            {
                series.Points.Clear();
            }
            var interp1 = Path.Combine(Directory.GetCurrentDirectory(), "AlGaAsSb_Interp.dat");
            var interp2 = Path.Combine(Directory.GetCurrentDirectory(), "GaInPAs_Interp.dat");
            if (materialBox.Text == "AlGaAsSb")
            {
                using (StreamReader sr = new StreamReader(interp1))
                {
                    string line;
                    int counter = 0;
                    while ((line = sr.ReadLine()) != null)
                    {
                        if (counter == 1)
                        {
                            var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                            string x = array[0];
                            string m_eff = array[2];
                            string Ev_hh = array[3];
                            string Ev_lh = array[4];
                            string Ev_so = array[5];
                            string Ec = array[6];
                            chart_masses.Series["m_eff"].Points.AddXY(x, m_eff);
                            chart_extremas.Series["Ev_hh"].Points.AddXY(x, Ev_hh);
                            chart_extremas.Series["Ev_lh"].Points.AddXY(x, Ev_lh);
                            chart_extremas.Series["Ev_so"].Points.AddXY(x, Ev_so);
                            chart_extremas.Series["Ec"].Points.AddXY(x, Ec);
                        }
                        if (counter != 1) counter++;

                    }
                    sr.Close();
                }
            }
            else if (materialBox.Text == "GaInPAs")
            {
                using (StreamReader sr = new StreamReader(interp2))
                {
                    string line;
                    int counter = 0;
                    while ((line = sr.ReadLine()) != null)
                    {
                        if (counter == 1)
                        {
                            var array = line.Split(new string[] { "\t \t" }, StringSplitOptions.RemoveEmptyEntries);
                            chart_masses.Series["m_eff"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[2]));
                            chart_extremas.Series["Ev_hh"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[3]));
                            chart_extremas.Series["Ev_lh"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[4]));
                            chart_extremas.Series["Ev_so"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[5]));
                            chart_extremas.Series["Ec"].Points.AddXY(Convert.ToString(array[0]), Convert.ToString(array[6]));
                        }
                        if (counter != 1) counter++;

                    }
                    sr.Close();
                }
            }

        }

        private void ENERGYCHART_Click(object sender, EventArgs e)
        {

        }
    }
}
