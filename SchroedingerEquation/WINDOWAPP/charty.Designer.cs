namespace Apka
{
    partial class charty
    {
        /// <summary> 
        /// Wymagana zmienna projektanta.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Wyczyść wszystkie używane zasoby.
        /// </summary>
        /// <param name="disposing">prawda, jeżeli zarządzane zasoby powinny zostać zlikwidowane; Fałsz w przeciwnym wypadku.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod wygenerowany przez Projektanta składników

        /// <summary> 
        /// Metoda wymagana do obsługi projektanta — nie należy modyfikować 
        /// jej zawartości w edytorze kodu.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series5 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series6 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series7 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series8 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title1 = new System.Windows.Forms.DataVisualization.Charting.Title();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series9 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title2 = new System.Windows.Forms.DataVisualization.Charting.Title();
            this.layoutInterpol = new System.Windows.Forms.TableLayoutPanel();
            this.Overlapping_printer = new System.Windows.Forms.Label();
            this.Eg_printer = new System.Windows.Forms.Label();
            this.ENERGYCHART = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.GaInPAs = new System.Windows.Forms.TableLayoutPanel();
            this.chart_extremas = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.chart_masses = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.materialBox = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.layoutInterpol.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ENERGYCHART)).BeginInit();
            this.GaInPAs.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart_extremas)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart_masses)).BeginInit();
            this.SuspendLayout();
            // 
            // layoutInterpol
            // 
            this.layoutInterpol.ColumnCount = 1;
            this.layoutInterpol.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.layoutInterpol.Controls.Add(this.Overlapping_printer, 0, 5);
            this.layoutInterpol.Controls.Add(this.Eg_printer, 0, 4);
            this.layoutInterpol.Controls.Add(this.ENERGYCHART, 0, 0);
            this.layoutInterpol.Controls.Add(this.GaInPAs, 0, 2);
            this.layoutInterpol.Controls.Add(this.materialBox, 0, 1);
            this.layoutInterpol.Controls.Add(this.label1, 0, 3);
            this.layoutInterpol.Dock = System.Windows.Forms.DockStyle.Fill;
            this.layoutInterpol.Location = new System.Drawing.Point(0, 0);
            this.layoutInterpol.Name = "layoutInterpol";
            this.layoutInterpol.RowCount = 6;
            this.layoutInterpol.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 43.68932F));
            this.layoutInterpol.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 3.883495F));
            this.layoutInterpol.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 49.51456F));
            this.layoutInterpol.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 2.912621F));
            this.layoutInterpol.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.layoutInterpol.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.layoutInterpol.Size = new System.Drawing.Size(885, 601);
            this.layoutInterpol.TabIndex = 0;
            this.layoutInterpol.Paint += new System.Windows.Forms.PaintEventHandler(this.tableLayout_Paint);
            // 
            // Overlapping_printer
            // 
            this.Overlapping_printer.AutoSize = true;
            this.Overlapping_printer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Overlapping_printer.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.Overlapping_printer.Location = new System.Drawing.Point(3, 579);
            this.Overlapping_printer.Name = "Overlapping_printer";
            this.Overlapping_printer.Size = new System.Drawing.Size(879, 22);
            this.Overlapping_printer.TabIndex = 10;
            this.Overlapping_printer.Text = "Overlapping intergral  \\int Psi_v*Psi_c = ";
            this.Overlapping_printer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Eg_printer
            // 
            this.Eg_printer.AutoSize = true;
            this.Eg_printer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Eg_printer.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.Eg_printer.Location = new System.Drawing.Point(3, 559);
            this.Eg_printer.Name = "Eg_printer";
            this.Eg_printer.Size = new System.Drawing.Size(879, 20);
            this.Eg_printer.TabIndex = 9;
            this.Eg_printer.Text = "EG = eV";
            this.Eg_printer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ENERGYCHART
            // 
            chartArea1.AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.True;
            chartArea1.AxisX.IsLabelAutoFit = false;
            chartArea1.AxisX.LabelAutoFitStyle = ((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles)((((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.IncreaseFont | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.DecreaseFont) 
            | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.LabelsAngleStep30) 
            | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.WordWrap)));
            chartArea1.AxisX.LabelStyle.IntervalOffset = 0D;
            chartArea1.AxisX.LabelStyle.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Auto;
            chartArea1.AxisX.LabelStyle.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Auto;
            chartArea1.AxisX.MajorGrid.Interval = 0D;
            chartArea1.AxisX.MajorGrid.IntervalOffset = 0D;
            chartArea1.AxisX.MajorGrid.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea1.AxisX.MajorGrid.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea1.AxisX.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.NotSet;
            chartArea1.AxisX.MajorTickMark.Interval = 0D;
            chartArea1.AxisX.MajorTickMark.IntervalOffset = 0D;
            chartArea1.AxisX.MajorTickMark.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Auto;
            chartArea1.AxisX.MajorTickMark.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Auto;
            chartArea1.AxisX.MajorTickMark.TickMarkStyle = System.Windows.Forms.DataVisualization.Charting.TickMarkStyle.InsideArea;
            chartArea1.AxisX.ScaleBreakStyle.Enabled = true;
            chartArea1.AxisX.ScaleBreakStyle.StartFromZero = System.Windows.Forms.DataVisualization.Charting.StartFromZero.Yes;
            chartArea1.AxisX.Title = "x[A]";
            chartArea1.AxisY.MajorGrid.Enabled = false;
            chartArea1.AxisY.MajorTickMark.TickMarkStyle = System.Windows.Forms.DataVisualization.Charting.TickMarkStyle.InsideArea;
            chartArea1.AxisY.Title = "Energy[eV]";
            chartArea1.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea1.Name = "ChartArea1";
            this.ENERGYCHART.ChartAreas.Add(chartArea1);
            this.ENERGYCHART.Dock = System.Windows.Forms.DockStyle.Fill;
            legend1.Alignment = System.Drawing.StringAlignment.Center;
            legend1.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Left;
            legend1.MaximumAutoSize = 15F;
            legend1.Name = "Legend1";
            legend1.Title = "LEGEND";
            this.ENERGYCHART.Legends.Add(legend1);
            this.ENERGYCHART.Location = new System.Drawing.Point(3, 3);
            this.ENERGYCHART.Name = "ENERGYCHART";
            series1.BorderWidth = 2;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine;
            series1.Legend = "Legend1";
            series1.Name = "Ev_hh";
            series2.BorderWidth = 2;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine;
            series2.Legend = "Legend1";
            series2.Name = "Ev_lh";
            series3.BorderWidth = 2;
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine;
            series3.Legend = "Legend1";
            series3.Name = "Ev_so";
            series4.BorderWidth = 2;
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine;
            series4.Legend = "Legend1";
            series4.Name = "Ec";
            this.ENERGYCHART.Series.Add(series1);
            this.ENERGYCHART.Series.Add(series2);
            this.ENERGYCHART.Series.Add(series3);
            this.ENERGYCHART.Series.Add(series4);
            this.ENERGYCHART.Size = new System.Drawing.Size(879, 239);
            this.ENERGYCHART.TabIndex = 0;
            this.ENERGYCHART.Text = "chart1";
            this.ENERGYCHART.Click += new System.EventHandler(this.ENERGYCHART_Click);
            // 
            // GaInPAs
            // 
            this.GaInPAs.ColumnCount = 2;
            this.GaInPAs.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 57.56541F));
            this.GaInPAs.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 42.43459F));
            this.GaInPAs.Controls.Add(this.chart_extremas, 0, 0);
            this.GaInPAs.Controls.Add(this.chart_masses, 1, 0);
            this.GaInPAs.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GaInPAs.Location = new System.Drawing.Point(3, 269);
            this.GaInPAs.Name = "GaInPAs";
            this.GaInPAs.RowCount = 1;
            this.GaInPAs.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.GaInPAs.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 301F));
            this.GaInPAs.Size = new System.Drawing.Size(879, 271);
            this.GaInPAs.TabIndex = 6;
            // 
            // chart_extremas
            // 
            chartArea2.AxisX.Title = "x(taking y as a parameter)";
            chartArea2.AxisY.Title = "Energy[eV]";
            chartArea2.Name = "ChartArea1";
            this.chart_extremas.ChartAreas.Add(chartArea2);
            this.chart_extremas.Dock = System.Windows.Forms.DockStyle.Fill;
            legend2.Alignment = System.Drawing.StringAlignment.Center;
            legend2.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Top;
            legend2.MaximumAutoSize = 15F;
            legend2.Name = "Legend1";
            this.chart_extremas.Legends.Add(legend2);
            this.chart_extremas.Location = new System.Drawing.Point(3, 3);
            this.chart_extremas.Name = "chart_extremas";
            series5.BorderWidth = 2;
            series5.ChartArea = "ChartArea1";
            series5.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series5.Legend = "Legend1";
            series5.MarkerBorderWidth = 2;
            series5.Name = "Ev_hh";
            series6.BorderWidth = 2;
            series6.ChartArea = "ChartArea1";
            series6.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series6.Legend = "Legend1";
            series6.MarkerBorderWidth = 2;
            series6.Name = "Ev_lh";
            series7.BorderWidth = 2;
            series7.ChartArea = "ChartArea1";
            series7.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series7.Legend = "Legend1";
            series7.MarkerBorderWidth = 2;
            series7.Name = "Ev_so";
            series8.BorderWidth = 2;
            series8.ChartArea = "ChartArea1";
            series8.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series8.Legend = "Legend1";
            series8.MarkerBorderWidth = 2;
            series8.Name = "Ec";
            this.chart_extremas.Series.Add(series5);
            this.chart_extremas.Series.Add(series6);
            this.chart_extremas.Series.Add(series7);
            this.chart_extremas.Series.Add(series8);
            this.chart_extremas.Size = new System.Drawing.Size(499, 295);
            this.chart_extremas.TabIndex = 0;
            this.chart_extremas.Text = "AlGaAsSb";
            title1.Alignment = System.Drawing.ContentAlignment.TopCenter;
            title1.BackColor = System.Drawing.Color.Transparent;
            title1.BackImageAlignment = System.Windows.Forms.DataVisualization.Charting.ChartImageAlignmentStyle.Top;
            title1.IsDockedInsideChartArea = false;
            title1.Name = "extremas";
            title1.Text = "Energy extremas";
            this.chart_extremas.Titles.Add(title1);
            // 
            // chart_masses
            // 
            chartArea3.AxisX.Title = "x(taking y as a parameter)";
            chartArea3.AxisY.Title = "m_eff";
            chartArea3.Name = "ChartArea1";
            this.chart_masses.ChartAreas.Add(chartArea3);
            this.chart_masses.Dock = System.Windows.Forms.DockStyle.Fill;
            legend3.Alignment = System.Drawing.StringAlignment.Center;
            legend3.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Top;
            legend3.ItemColumnSpacing = 10;
            legend3.MaximumAutoSize = 10F;
            legend3.Name = "Legend1";
            legend3.TableStyle = System.Windows.Forms.DataVisualization.Charting.LegendTableStyle.Wide;
            legend3.TextWrapThreshold = 10;
            this.chart_masses.Legends.Add(legend3);
            this.chart_masses.Location = new System.Drawing.Point(508, 3);
            this.chart_masses.Name = "chart_masses";
            series9.BorderWidth = 2;
            series9.ChartArea = "ChartArea1";
            series9.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            series9.Legend = "Legend1";
            series9.Name = "m_eff";
            series9.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            this.chart_masses.Series.Add(series9);
            this.chart_masses.Size = new System.Drawing.Size(368, 295);
            this.chart_masses.TabIndex = 1;
            this.chart_masses.Text = "GaInPAs";
            title2.IsDockedInsideChartArea = false;
            title2.Name = "GaInPAs";
            title2.Text = "Effective masses";
            this.chart_masses.Titles.Add(title2);
            // 
            // materialBox
            // 
            this.materialBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.materialBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.materialBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.25F);
            this.materialBox.FormattingEnabled = true;
            this.materialBox.Items.AddRange(new object[] {
            "AlGaAsSb",
            "GaInPAs"});
            this.materialBox.Location = new System.Drawing.Point(3, 248);
            this.materialBox.Name = "materialBox";
            this.materialBox.Size = new System.Drawing.Size(879, 15);
            this.materialBox.TabIndex = 7;
            this.materialBox.SelectedValueChanged += new System.EventHandler(this.materialBox_SelectedValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label1.Location = new System.Drawing.Point(3, 543);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(879, 16);
            this.label1.TabIndex = 8;
            this.label1.Text = "SUB/Al_{x1}Ga_{1-x1}As_{y1}Sb_{1-y1}/Ga_{x2}In_{1-x2}P_{y2}As_{1-y2}/Al_{x3}Ga{1-" +
    "x3}As{y3}Sb{1-y3}/SUB";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // charty
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.layoutInterpol);
            this.Name = "charty";
            this.Size = new System.Drawing.Size(885, 601);
            this.Load += new System.EventHandler(this.charty_Load);
            this.layoutInterpol.ResumeLayout(false);
            this.layoutInterpol.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ENERGYCHART)).EndInit();
            this.GaInPAs.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart_extremas)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart_masses)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel layoutInterpol;
        private System.Windows.Forms.DataVisualization.Charting.Chart ENERGYCHART;
        private System.Windows.Forms.TableLayoutPanel GaInPAs;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart_extremas;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart_masses;
        private System.Windows.Forms.ListBox materialBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label Overlapping_printer;
        private System.Windows.Forms.Label Eg_printer;
    }
}
