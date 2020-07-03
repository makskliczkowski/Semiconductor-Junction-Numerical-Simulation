namespace Apka
{
    partial class stat
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
            this.whatToDo = new System.Windows.Forms.ComboBox();
            this.SCHRODCHART = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.layoutForControls = new System.Windows.Forms.TableLayoutPanel();
            this.k_change = new System.Windows.Forms.NumericUpDown();
            this.meff_change = new System.Windows.Forms.NumericUpDown();
            this.c_change = new System.Windows.Forms.NumericUpDown();
            this.b_change = new System.Windows.Forms.NumericUpDown();
            this.step_change = new System.Windows.Forms.NumericUpDown();
            this.starting_change = new System.Windows.Forms.NumericUpDown();
            this.ending_change = new System.Windows.Forms.NumericUpDown();
            this.eigstate_change = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.calculateSchrodinger = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.SCHRODCHART)).BeginInit();
            this.layoutForControls.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.k_change)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.meff_change)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.c_change)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.b_change)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.step_change)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.starting_change)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ending_change)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eigstate_change)).BeginInit();
            this.SuspendLayout();
            // 
            // whatToDo
            // 
            this.whatToDo.Dock = System.Windows.Forms.DockStyle.Top;
            this.whatToDo.FormattingEnabled = true;
            this.whatToDo.Items.AddRange(new object[] {
            "PARABOLIC",
            "MATERIALS"});
            this.whatToDo.Location = new System.Drawing.Point(0, 0);
            this.whatToDo.Name = "whatToDo";
            this.whatToDo.Size = new System.Drawing.Size(885, 21);
            this.whatToDo.TabIndex = 14;
            this.whatToDo.TextChanged += new System.EventHandler(this.whatToDo_TextChanged);
            // 
            // SCHRODCHART
            // 
            this.SCHRODCHART.BackColor = System.Drawing.Color.Black;
            chartArea1.AxisX.LabelStyle.ForeColor = System.Drawing.Color.White;
            chartArea1.AxisX.LineColor = System.Drawing.Color.White;
            chartArea1.AxisX.MajorGrid.Interval = 0D;
            chartArea1.AxisX.MajorTickMark.Interval = 0D;
            chartArea1.AxisX.MajorTickMark.LineColor = System.Drawing.Color.White;
            chartArea1.AxisX.Title = "x[A]";
            chartArea1.AxisX.TitleForeColor = System.Drawing.Color.White;
            chartArea1.AxisY.LabelStyle.ForeColor = System.Drawing.Color.White;
            chartArea1.AxisY.LineColor = System.Drawing.Color.White;
            chartArea1.AxisY.MajorGrid.LineColor = System.Drawing.Color.White;
            chartArea1.AxisY.MajorTickMark.LineColor = System.Drawing.Color.White;
            chartArea1.AxisY.Title = "E[eV]";
            chartArea1.AxisY.TitleForeColor = System.Drawing.Color.White;
            chartArea1.Name = "ChartArea1";
            this.SCHRODCHART.ChartAreas.Add(chartArea1);
            this.SCHRODCHART.Dock = System.Windows.Forms.DockStyle.Fill;
            legend1.AutoFitMinFontSize = 6;
            legend1.BackColor = System.Drawing.Color.Black;
            legend1.ForeColor = System.Drawing.Color.White;
            legend1.LegendStyle = System.Windows.Forms.DataVisualization.Charting.LegendStyle.Column;
            legend1.Name = "Legend1";
            legend1.TableStyle = System.Windows.Forms.DataVisualization.Charting.LegendTableStyle.Tall;
            legend1.Title = "hhh";
            this.SCHRODCHART.Legends.Add(legend1);
            this.SCHRODCHART.Location = new System.Drawing.Point(0, 97);
            this.SCHRODCHART.Name = "SCHRODCHART";
            this.SCHRODCHART.Size = new System.Drawing.Size(885, 504);
            this.SCHRODCHART.TabIndex = 15;
            this.SCHRODCHART.Text = "schrodCalcul";
            // 
            // layoutForControls
            // 
            this.layoutForControls.ColumnCount = 8;
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.49765F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.49766F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.49766F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.49766F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.49766F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.50391F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.50391F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 12.50391F));
            this.layoutForControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.layoutForControls.Controls.Add(this.k_change, 0, 1);
            this.layoutForControls.Controls.Add(this.meff_change, 0, 1);
            this.layoutForControls.Controls.Add(this.c_change, 0, 1);
            this.layoutForControls.Controls.Add(this.b_change, 0, 1);
            this.layoutForControls.Controls.Add(this.step_change, 0, 1);
            this.layoutForControls.Controls.Add(this.starting_change, 0, 1);
            this.layoutForControls.Controls.Add(this.ending_change, 1, 1);
            this.layoutForControls.Controls.Add(this.eigstate_change, 0, 1);
            this.layoutForControls.Controls.Add(this.label8, 7, 0);
            this.layoutForControls.Controls.Add(this.label7, 6, 0);
            this.layoutForControls.Controls.Add(this.label6, 5, 0);
            this.layoutForControls.Controls.Add(this.label5, 4, 0);
            this.layoutForControls.Controls.Add(this.label4, 3, 0);
            this.layoutForControls.Controls.Add(this.label3, 2, 0);
            this.layoutForControls.Controls.Add(this.label2, 1, 0);
            this.layoutForControls.Controls.Add(this.label1, 0, 0);
            this.layoutForControls.Dock = System.Windows.Forms.DockStyle.Top;
            this.layoutForControls.Location = new System.Drawing.Point(0, 21);
            this.layoutForControls.Name = "layoutForControls";
            this.layoutForControls.RowCount = 2;
            this.layoutForControls.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.layoutForControls.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.layoutForControls.Size = new System.Drawing.Size(885, 44);
            this.layoutForControls.TabIndex = 16;
            // 
            // k_change
            // 
            this.k_change.BackColor = System.Drawing.SystemColors.InfoText;
            this.k_change.DecimalPlaces = 5;
            this.k_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.k_change.ForeColor = System.Drawing.SystemColors.Info;
            this.k_change.Increment = new decimal(new int[] {
            5,
            0,
            0,
            131072});
            this.k_change.Location = new System.Drawing.Point(3, 25);
            this.k_change.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.k_change.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.k_change.Name = "k_change";
            this.k_change.Size = new System.Drawing.Size(104, 20);
            this.k_change.TabIndex = 15;
            this.k_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.k_change.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // meff_change
            // 
            this.meff_change.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.meff_change.DecimalPlaces = 2;
            this.meff_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.meff_change.ForeColor = System.Drawing.SystemColors.Window;
            this.meff_change.Location = new System.Drawing.Point(333, 25);
            this.meff_change.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.meff_change.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            65536});
            this.meff_change.Name = "meff_change";
            this.meff_change.Size = new System.Drawing.Size(104, 20);
            this.meff_change.TabIndex = 14;
            this.meff_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.meff_change.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // c_change
            // 
            this.c_change.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.c_change.DecimalPlaces = 2;
            this.c_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.c_change.ForeColor = System.Drawing.SystemColors.Window;
            this.c_change.Location = new System.Drawing.Point(223, 25);
            this.c_change.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.c_change.Name = "c_change";
            this.c_change.Size = new System.Drawing.Size(104, 20);
            this.c_change.TabIndex = 13;
            this.c_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // b_change
            // 
            this.b_change.BackColor = System.Drawing.SystemColors.MenuText;
            this.b_change.DecimalPlaces = 2;
            this.b_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.b_change.ForeColor = System.Drawing.SystemColors.Window;
            this.b_change.Location = new System.Drawing.Point(113, 25);
            this.b_change.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.b_change.Name = "b_change";
            this.b_change.Size = new System.Drawing.Size(104, 20);
            this.b_change.TabIndex = 12;
            this.b_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // step_change
            // 
            this.step_change.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.step_change.DecimalPlaces = 3;
            this.step_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.step_change.ForeColor = System.Drawing.SystemColors.Window;
            this.step_change.Increment = new decimal(new int[] {
            5,
            0,
            0,
            131072});
            this.step_change.Location = new System.Drawing.Point(443, 25);
            this.step_change.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.step_change.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.step_change.Name = "step_change";
            this.step_change.Size = new System.Drawing.Size(104, 20);
            this.step_change.TabIndex = 11;
            this.step_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.step_change.Value = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            // 
            // starting_change
            // 
            this.starting_change.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.starting_change.DecimalPlaces = 2;
            this.starting_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.starting_change.ForeColor = System.Drawing.SystemColors.Window;
            this.starting_change.Location = new System.Drawing.Point(663, 25);
            this.starting_change.Maximum = new decimal(new int[] {
            25,
            0,
            0,
            -2147418112});
            this.starting_change.Minimum = new decimal(new int[] {
            50,
            0,
            0,
            -2147483648});
            this.starting_change.Name = "starting_change";
            this.starting_change.Size = new System.Drawing.Size(104, 20);
            this.starting_change.TabIndex = 10;
            this.starting_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.starting_change.Value = new decimal(new int[] {
            35,
            0,
            0,
            -2147418112});
            // 
            // ending_change
            // 
            this.ending_change.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.ending_change.DecimalPlaces = 2;
            this.ending_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.ending_change.ForeColor = System.Drawing.SystemColors.Window;
            this.ending_change.Location = new System.Drawing.Point(773, 25);
            this.ending_change.Maximum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.ending_change.Minimum = new decimal(new int[] {
            35,
            0,
            0,
            65536});
            this.ending_change.Name = "ending_change";
            this.ending_change.Size = new System.Drawing.Size(109, 20);
            this.ending_change.TabIndex = 9;
            this.ending_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ending_change.Value = new decimal(new int[] {
            35,
            0,
            0,
            65536});
            // 
            // eigstate_change
            // 
            this.eigstate_change.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.eigstate_change.Dock = System.Windows.Forms.DockStyle.Top;
            this.eigstate_change.ForeColor = System.Drawing.SystemColors.Window;
            this.eigstate_change.Location = new System.Drawing.Point(553, 25);
            this.eigstate_change.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.eigstate_change.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.eigstate_change.Name = "eigstate_change";
            this.eigstate_change.Size = new System.Drawing.Size(104, 20);
            this.eigstate_change.TabIndex = 8;
            this.eigstate_change.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.eigstate_change.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label8.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label8.Location = new System.Drawing.Point(773, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(109, 22);
            this.label8.TabIndex = 7;
            this.label8.Text = "ending point";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label7.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label7.Location = new System.Drawing.Point(663, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(104, 22);
            this.label7.TabIndex = 6;
            this.label7.Text = "starting point";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
            this.label6.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label6.Location = new System.Drawing.Point(553, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(104, 22);
            this.label6.TabIndex = 5;
            this.label6.Text = "eigenstates number";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label5.Location = new System.Drawing.Point(443, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(104, 22);
            this.label5.TabIndex = 4;
            this.label5.Text = "step = ";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label4.Location = new System.Drawing.Point(333, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(104, 22);
            this.label4.TabIndex = 3;
            this.label4.Text = "meff  = ";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label3.Location = new System.Drawing.Point(223, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(104, 22);
            this.label3.TabIndex = 2;
            this.label3.Text = "c = ";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Location = new System.Drawing.Point(113, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(104, 22);
            this.label2.TabIndex = 1;
            this.label2.Text = "b = ";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(3, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(104, 22);
            this.label1.TabIndex = 0;
            this.label1.Text = "V(x) = kx^2 + bx +c, k=";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // calculateSchrodinger
            // 
            this.calculateSchrodinger.Dock = System.Windows.Forms.DockStyle.Top;
            this.calculateSchrodinger.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.calculateSchrodinger.Font = new System.Drawing.Font("Terminator Two", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.calculateSchrodinger.ForeColor = System.Drawing.SystemColors.Control;
            this.calculateSchrodinger.Location = new System.Drawing.Point(0, 65);
            this.calculateSchrodinger.Name = "calculateSchrodinger";
            this.calculateSchrodinger.Size = new System.Drawing.Size(885, 32);
            this.calculateSchrodinger.TabIndex = 17;
            this.calculateSchrodinger.Text = "CALCULATE SCHRODINGER EQUATION";
            this.calculateSchrodinger.UseVisualStyleBackColor = true;
            this.calculateSchrodinger.Click += new System.EventHandler(this.calculateSchrodinger_Click);
            // 
            // stat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(13)))), ((int)(((byte)(13)))), ((int)(((byte)(13)))));
            this.Controls.Add(this.SCHRODCHART);
            this.Controls.Add(this.calculateSchrodinger);
            this.Controls.Add(this.layoutForControls);
            this.Controls.Add(this.whatToDo);
            this.Name = "stat";
            this.Size = new System.Drawing.Size(885, 601);
            this.Load += new System.EventHandler(this.stat_Load);
            ((System.ComponentModel.ISupportInitialize)(this.SCHRODCHART)).EndInit();
            this.layoutForControls.ResumeLayout(false);
            this.layoutForControls.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.k_change)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.meff_change)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.c_change)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.b_change)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.step_change)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.starting_change)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ending_change)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eigstate_change)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox whatToDo;
        private System.Windows.Forms.DataVisualization.Charting.Chart SCHRODCHART;
        private System.Windows.Forms.TableLayoutPanel layoutForControls;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown k_change;
        private System.Windows.Forms.NumericUpDown meff_change;
        private System.Windows.Forms.NumericUpDown c_change;
        private System.Windows.Forms.NumericUpDown b_change;
        private System.Windows.Forms.NumericUpDown step_change;
        private System.Windows.Forms.NumericUpDown starting_change;
        private System.Windows.Forms.NumericUpDown ending_change;
        private System.Windows.Forms.NumericUpDown eigstate_change;
        private System.Windows.Forms.Button calculateSchrodinger;
    }
}
