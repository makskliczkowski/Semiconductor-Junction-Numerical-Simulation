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

    public partial class stat : UserControl
    {
        string[] parametersForMaterials;
        public void setParametersForMaterials(string[] argv)
        {
            /*
            0) x1
	        1) y1
	        2) x2
	        3) y2
	        4) x3
	        5) y3
	        6) bool include strain
	        7) substrate?
	        8)Substratefinish
            9)T
	        10)FirstMaterial_finish_point
	        11)SecondMaterial_finish_point
            12)width
                */
            parametersForMaterials = argv;
        }

        double[][] HERMIT = new double[][] { new double[] { 1.0 }, new double[] { 0.0, 2.0 }, new double[] { -2.0, 0.0, 4.0 }, new double[] { 0.0, -12.0, 0.0, 8.0 }, new double[] { 12.0, 0.0, -48.0, 0.0, 16.0 }, new double[] { 0.0, 120.0, 0.0, -160.0, 0.0, 32.0 }, new double[] { -120.0, 0.0, 720.0, 0.0, -480.0, 0.0, 64.0 }, new double[] { 0.0, -1680.0, 0.0, 3360.0, 0.0, -1344.0, 0.0, 128.0 }, new double[] { 1680.0, 0.0, -13440.0, 0.0, 13440.0, 0.0, -3584.0, 0.0, 256.0 }, new double[] { 0.0, 30240.0, 0.0, -80640.0, 0.0, 48384.0, 0.0, -9216.0, 0.0, 512.0 } };
        public stat()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }
        private double parabolicEnergy(double k, double n,double mass)
        {
            //mass is in me units so we have to multiply by me; get hbar also
            //k in eV/A*A
            double hbar = 6.5821e-16; //1.054e-34;////eV*s
            double mel = 9.10938356e-31; //kg
            double m = mass * mel;
            double omega = Math.Sqrt(k / (m));
            double energy = (n + 0.5) * hbar * omega;
            return energy;
        }
        private double parabolicWavefunction(double k, int n, double mass,double x)
        {
            //https://scipython.com/blog/the-harmonic-oscillator-wavefunctions/
            double hbar = 6.5821e-16;//eV*s
            double mel = 9.10938356e-31; //kg
            double m = mass * mel;
            double omega = Math.Sqrt(k / m);
            double alpha = Math.Sqrt((m *k)/ (hbar *hbar));
            double ksi = x*Math.Sqrt(alpha);

            
            double Hn = 0;
            for(int i = 0; i <= n; i++)
            {
                Hn = Hn + HERMIT[n][i] * Math.Pow(ksi, i);
            }
            double N_n = (1.0 /( Math.Sqrt(Factorial(n) * Math.Pow(2, n)*Math.Sqrt(Math.PI))));// * Math.Sqrt(alpha/Math.PI);
            double phi = N_n * Hn * Math.Exp(- 0.5* ksi * ksi ); 
            return phi;
        }
        int Factorial(int n)
        {
            if (n == 0) return 1;
            if (n == 1) return 1;
            else return n * Factorial(n - 1);
        }
        private void whatToDo_TextChanged(object sender, EventArgs e)
        {
            if (whatToDo.Text == "MATERIALS") layoutForControls.Hide();
            else layoutForControls.Show();
        }

        private void stat_Load(object sender, EventArgs e)
        {
            whatToDo.Text = "PARABOLIC";
        }
        private void calculateParabolic()
        {
            var format = new NumberFormatInfo();
            format.NegativeSign = "-";
            format.NumberDecimalSeparator = ".";
            const double G = 4.2058;
            SCHRODCHART.Series.Clear();
            SCHRODCHART.Series.Add("Potential");
            SCHRODCHART.Series["Potential"].ChartType = SeriesChartType.Spline;
            //foreach (var series in SCHRODCHART.Series)
            //{
            //   series.Points.Clear(); //clearing points
            // }
            /*IF(PARABOLIC) ax^2+bx+c
            2) a
            3) b
            4) c
            5) meff
            6) stepInDiscretization
            7) DiscretizationPoints
            8) EigenstatesNum
            9) Starting point
            */
            string what = "PARABOLIC";
            double a, b, c, meff, step, starting,ending;
            int discretizationPoints, eigenstatesNum;
            a = Decimal.ToDouble(k_change.Value);
            b = Decimal.ToDouble(b_change.Value);
            c = Decimal.ToDouble(c_change.Value);
            meff = Decimal.ToDouble(meff_change.Value);
            step = Decimal.ToDouble(step_change.Value);
            eigenstatesNum = Decimal.ToInt32(eigstate_change.Value);
            starting = Decimal.ToDouble(starting_change.Value);
            ending = Decimal.ToDouble(ending_change.Value);
            discretizationPoints = Convert.ToInt32((ending-starting)/step);

            //====================================================EXE PROCESS-------------------------------------
            string cParams;
            cParams = what;//what
            cParams += " " + Convert.ToString(a, System.Globalization.CultureInfo.InvariantCulture); //a
            cParams += " " + Convert.ToString(b, System.Globalization.CultureInfo.InvariantCulture); //a
            cParams += " " + Convert.ToString(c, System.Globalization.CultureInfo.InvariantCulture); //a
            cParams += " " + Convert.ToString(meff, System.Globalization.CultureInfo.InvariantCulture); //a
            cParams += " " + Convert.ToString(step, System.Globalization.CultureInfo.InvariantCulture); //a
            cParams += " " + Convert.ToString(discretizationPoints, System.Globalization.CultureInfo.InvariantCulture); //a
            cParams += " " + Convert.ToString(eigenstatesNum, System.Globalization.CultureInfo.InvariantCulture); //a
            cParams += " " + Convert.ToString(starting, System.Globalization.CultureInfo.InvariantCulture); //a

            var filePath = Path.Combine(Directory.GetCurrentDirectory(), "LasersAndMaterials.exe");

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
            }
            catch
            {
                MessageBox.Show("Couldn't calculate, try again, maybe parameters are wrong", "Error 4001", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            //========================================ADDING PLOTS========================================
            for (int i = 0; i < eigenstatesNum; i++)
            {
                SCHRODCHART.Series.Add(Convert.ToString(i,format));//adding series to the chart!!!  //wavefunctions
                SCHRODCHART.Series[Convert.ToString(i,format)].ChartType = SeriesChartType.Spline;
                SCHRODCHART.Series.Add("Energy" + Convert.ToString(i,format));//adding series to the chart!!! numerical energy
                SCHRODCHART.Series["Energy" + Convert.ToString(i,format)].ChartType = SeriesChartType.Spline;
                SCHRODCHART.Series.Add("AnEnergy" + Convert.ToString(i, format));//adding series to the chart!!! analitical energy
                SCHRODCHART.Series["AnEnergy" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
                SCHRODCHART.Series.Add("An" + Convert.ToString(i, format));//adding series to the chart!!! analitical wavefunctions
                SCHRODCHART.Series["An" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
            }
            //=----------------------------------------DRAWING GRAPH-----------------------------------------------------------------
            string[] energies = new string[eigenstatesNum];
            double[] anEnergies = new double[eigenstatesNum];
            string[,] wavefunctions = new string[eigenstatesNum,discretizationPoints];
            double[,] anWavefunctions = new double[eigenstatesNum,discretizationPoints];
            //-------reading energies and wavefunctions
            double[] sumForNorm = new double[eigenstatesNum];
                using (StreamReader sr = new StreamReader("energies.dat"))
            {
                string line;
                int counter = 0;
                while ((line = sr.ReadLine()) != null)
                {
                   energies[counter] = line;
                   anEnergies[counter] = parabolicEnergy(a, counter, meff);
                    sumForNorm[counter] = 0;
                   counter++;
                }
                sr.Close();
            }

            using (StreamReader sr = new StreamReader("wavefunctions.dat"))
            {
                string line;
                int counter = 0;

                while ((line = sr.ReadLine()) != null)
                {
                    var array = line.Split(new string[] { "\t\t" }, StringSplitOptions.RemoveEmptyEntries);
                    double x = starting + (counter) * step;
                    for (int i = 1; i <= eigenstatesNum; i++)
                    {
                        wavefunctions[i - 1,counter] = array[i];
                        anWavefunctions[i - 1, counter] = parabolicWavefunction(a, i-1, meff, x);
                        sumForNorm[i-1] += anWavefunctions[i - 1, counter] * anWavefunctions[i - 1, counter];
                    }
                    counter++;
                }
                sr.Close();
            }

            for(int i =0; i < eigenstatesNum; i++)
            {
                double norm = Math.Sqrt(sumForNorm[i])*Math.Sqrt(step);
                for(int j=0;j< discretizationPoints; j++)
                {
                    anWavefunctions[i, j] = anWavefunctions[i, j] / norm;
                }
            }

            //------------------------------------------------
            try
            {

                double E0 = Convert.ToDouble(energies[0], format);
                double G0 = 0.262468291;
                for (int i = 0; i < discretizationPoints; i++)
                {
                    double x = starting + i * step;
                    double V = ((a * x * x/2) + b * x + c);//we will try in undimensiona;l
                    if ((i == 0 && V < E0) || i == discretizationPoints - 1 && V < E0)
                    {
                        //Checking if E0 is above potential limits
                        MessageBox.Show("Couldn't calculate, try again, all eigenvalues are above potential!", "Error 4002", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                    //Potential
                    SCHRODCHART.Series["Potential"].Points.AddXY(x, V);
                    for (int j = 0; j < eigenstatesNum; j++)
                    {
                        double energy = Convert.ToDouble(energies[j], format);
                        double anEnergy = anEnergies[j];
                        SCHRODCHART.Series["Energy" + Convert.ToString(j)].Points.AddXY(x, energy);
                        SCHRODCHART.Series["AnEnergy" + Convert.ToString(j)].Points.AddXY(x, anEnergies[j]);
                        double movedEigFun =Double.Parse(wavefunctions[j, i], format) + energy;
                        double movedAnEigFun = anWavefunctions[j, i] + anEnergies[j];
                        SCHRODCHART.Series[Convert.ToString(j, format)].Points.AddXY(x, movedEigFun);// plot the functions at the level of corresponding energies
                        SCHRODCHART.Series["An" + Convert.ToString(j, format)].Points.AddXY(x, movedAnEigFun);// plot the functions at the level of corresponding energies
                    }
                }
            }
            catch{
                MessageBox.Show("Couldn't calculate, try again, maybe parameters are wrong. Probably there's is no eigenvalues smaller than the potential borders", "Error 4003", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void calculateMaterials()
        {
            //-------------------------------------print format------------------------
            var format = new NumberFormatInfo();
            format.NegativeSign = "-";
            format.NumberDecimalSeparator = ".";
            const double G = 4.2058;
            //-------------------------------------------------------------------------
            SCHRODCHART.Series.Clear();
            SCHRODCHART.Series.Add("ValenceBand");
            SCHRODCHART.Series["ValenceBand"].ChartType = SeriesChartType.Spline;
            SCHRODCHART.Series.Add("ConductionBand");
            SCHRODCHART.Series["ConductionBand"].ChartType = SeriesChartType.Spline;

            /*IF(MATERIALS) ax^2+bx+c
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
            double width,substrateFinish;

            x1 = Convert.ToDouble(parametersForMaterials[0],format);//2
            y1 = Convert.ToDouble(parametersForMaterials[1], format);//3
            x2 = Convert.ToDouble(parametersForMaterials[2], format);//4
            y2 = Convert.ToDouble(parametersForMaterials[3], format);//5
            x3 = Convert.ToDouble(parametersForMaterials[4], format);//6
            y3 = Convert.ToDouble(parametersForMaterials[5], format);//7
            includeStrain = Convert.ToInt16(parametersForMaterials[6], format);//8
            substrate = parametersForMaterials[7];//9
            eigenstatesNum = Decimal.ToInt32(eigstate_change.Value);//10
            step = Decimal.ToDouble(step_change.Value);//11
            substrateFinish = Convert.ToDouble(parametersForMaterials[8], format);//13
            T = Convert.ToDouble(parametersForMaterials[9], format);//14
            firstFinish = Convert.ToDouble(parametersForMaterials[10], format);//15
            secondFinish = Convert.ToDouble(parametersForMaterials[11], format);//16
            width = Convert.ToDouble(parametersForMaterials[12], format);//17
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
            }
            catch
            {
                MessageBox.Show("Couldn't calculate, try again, maybe parameters are wrong", "Error 4001", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            //========================================ADDING PLOTS========================================
            for (int i = 0; i < eigenstatesNum; i++)
            {
                SCHRODCHART.Series.Add("CondWave" + Convert.ToString(i, format));//adding series to the chart!!!  //wavefunctions
                SCHRODCHART.Series["CondWave" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
                SCHRODCHART.Series.Add("EnergyCond" + Convert.ToString(i, format));//adding series to the chart!!! conduction band energy
                SCHRODCHART.Series["EnergyCond" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
                SCHRODCHART.Series.Add("EnergyVal" + Convert.ToString(i, format));//adding series to the chart!!! valence band energy
                SCHRODCHART.Series["EnergyVal" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
                SCHRODCHART.Series.Add("ValWave" + Convert.ToString(i, format));//adding series to the chart!!! analitical wavefunctions
                SCHRODCHART.Series["ValWave" + Convert.ToString(i, format)].ChartType = SeriesChartType.Spline;
            }
            //=----------------------------------------DRAWING GRAPH-----------------------------------------------------------------
            string[] energiesCond = new string[eigenstatesNum];
            string[] energiesVal = new string[eigenstatesNum];
            string[,] wavefunctionsVal = new string[eigenstatesNum, discretizationPoints];
            string[,] wavefunctionsCond = new string[eigenstatesNum, discretizationPoints];
            //-------reading energies and wavefunctions------------------------------------------------------------------------------
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
                    for (int i = 1; i <= eigenstatesNum; i++)
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
                    energiesVal[counter] = line;
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
                    for (int i = 1; i <= eigenstatesNum; i++)
                    {
                        wavefunctionsVal[i - 1, counter] = array[i];
                    }
                    counter++;
                }
                sr.Close();
            }
            //--------------------------------------------------------------------------------------------
            try
            {

                double EvalMax = Convert.ToDouble(energiesVal[eigenstatesNum-1], format);
                double EcondMin = Convert.ToDouble(energiesVal[0], format);
                MessageBox.Show("The band gap is" + Convert.ToString(EcondMin-EvalMax), "LOOK", MessageBoxButtons.OK, MessageBoxIcon.Information);
                double G0 = 0.262468291;
                for (int i = 0; i < discretizationPoints; i++)
                {
                    double x = 0 + i * step;
                    /*if ((i == 0 && V < E0) || i == discretizationPoints - 1 && V < E0)
                    {
                        //Checking if E0 is above potential limits
                        MessageBox.Show("Couldn't calculate, try again, all eigenvalues are above potential!", "Error 4002", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }*/
                    //Potential
                    //SCHRODCHART.Series["Potential"].Points.AddXY(x, V);
                    for (int j = 0; j < eigenstatesNum; j++)
                    {
                        double enCond = Convert.ToDouble(energiesCond[j], format);
                        double enVal = Convert.ToDouble(energiesVal[j], format);
                        SCHRODCHART.Series["EnergyCond" + Convert.ToString(j)].Points.AddXY(x, enCond);
                        SCHRODCHART.Series["EnergyVal" + Convert.ToString(j)].Points.AddXY(x, enVal);
                        double movedEigFunCond = Double.Parse(wavefunctionsCond[j, i], format) + enCond;
                        double movedEigFunVal = Double.Parse(wavefunctionsVal[j, i], format) + enVal;
                        SCHRODCHART.Series["CondWave" + Convert.ToString(j, format)].Points.AddXY(x, movedEigFunCond);// plot the functions at the level of corresponding energies
                        SCHRODCHART.Series["ValWave" + Convert.ToString(j, format)].Points.AddXY(x, movedEigFunVal);// plot the functions at the level of corresponding energies
                    }
                }
            }
            catch
            {
                MessageBox.Show("Couldn't calculate, try again, maybe parameters are wrong. Probably there's is no eigenvalues smaller than the potential borders", "Error 4003", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }


        }
        private void calculateSchrodinger_Click(object sender, EventArgs e) {

            if (whatToDo.Text == "PARABOLIC")
            {
                calculateParabolic();
            }
            else if(whatToDo.Text == "MATERIALS")
            {
                //Can do it from here but try to put it into main app
                //calculateMaterials();
            }

        }
    }
}
