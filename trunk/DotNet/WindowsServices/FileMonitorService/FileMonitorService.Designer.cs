namespace FileMonitorService
{
    partial class FileMonitorService
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.fileCreateCounter = new System.Diagnostics.PerformanceCounter();
            this.fileDeleteCounter = new System.Diagnostics.PerformanceCounter();
            this.fileRenameCounter = new System.Diagnostics.PerformanceCounter();
            this.fileChangeCounter = new System.Diagnostics.PerformanceCounter();
            ((System.ComponentModel.ISupportInitialize)(this.fileCreateCounter)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileDeleteCounter)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileRenameCounter)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileChangeCounter)).BeginInit();
            // 
            // fileCreateCounter
            // 
            this.fileCreateCounter.CategoryName = "File Monitor Service";
            this.fileCreateCounter.CounterName = "Files Created";
            // 
            // fileDeleteCounter
            // 
            this.fileDeleteCounter.CategoryName = "File Monitor Service";
            this.fileDeleteCounter.CounterName = "Files Deleted";
            // 
            // fileRenameCounter
            // 
            this.fileRenameCounter.CategoryName = "File Monitor Service";
            this.fileRenameCounter.CounterName = "Files Renamed";
            // 
            // fileChangeCounter
            // 
            this.fileChangeCounter.CategoryName = "File Monitor Service";
            this.fileChangeCounter.CounterName = "Files Changed";
            // 
            // FileMonitorService
            // 
            this.CanPauseAndContinue = true;
            this.ServiceName = "FileMonitorService";
            ((System.ComponentModel.ISupportInitialize)(this.fileCreateCounter)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileDeleteCounter)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileRenameCounter)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileChangeCounter)).EndInit();

        }

        #endregion

        private System.Diagnostics.PerformanceCounter fileCreateCounter;
        private System.Diagnostics.PerformanceCounter fileDeleteCounter;
        private System.Diagnostics.PerformanceCounter fileRenameCounter;
        private System.Diagnostics.PerformanceCounter fileChangeCounter;
    }
}
