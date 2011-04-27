using System;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Collections;
using System.Drawing;
using System.Reflection;
using System.Workflow.ComponentModel.Compiler;
using System.Workflow.ComponentModel.Serialization;
using System.Workflow.ComponentModel;
using System.Workflow.ComponentModel.Design;
using System.Workflow.Runtime;
using System.Workflow.Activities;
using System.Workflow.Activities.Rules;

namespace HelloWF
{
    partial class Workflow1
    {
        #region Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCode]
        private void InitializeComponent()
        {
            this.CanModifyActivities = true;
            System.Workflow.Activities.CodeCondition codecondition1 = new System.Workflow.Activities.CodeCondition();
            this.codeActivity3 = new System.Workflow.Activities.CodeActivity();
            this.faultHandlerActivity1 = new System.Workflow.ComponentModel.FaultHandlerActivity();
            this.faultHandlersActivity1 = new System.Workflow.ComponentModel.FaultHandlersActivity();
            this.cancellationHandlerActivity1 = new System.Workflow.ComponentModel.CancellationHandlerActivity();
            this.codeActivity2 = new System.Workflow.Activities.CodeActivity();
            this.codeActivity1 = new System.Workflow.Activities.CodeActivity();
            this.sequenceActivity1 = new System.Workflow.Activities.SequenceActivity();
            this.delayActivity2 = new System.Workflow.Activities.DelayActivity();
            this.whileActivity1 = new System.Workflow.Activities.WhileActivity();
            this.delayActivity1 = new System.Workflow.Activities.DelayActivity();
            // 
            // codeActivity3
            // 
            this.codeActivity3.Name = "codeActivity3";
            this.codeActivity3.ExecuteCode += new System.EventHandler(this.codeActivity3_ExecuteCode);
            // 
            // faultHandlerActivity1
            // 
            this.faultHandlerActivity1.Activities.Add(this.codeActivity3);
            this.faultHandlerActivity1.FaultType = typeof(System.Exception);
            this.faultHandlerActivity1.Name = "faultHandlerActivity1";
            // 
            // faultHandlersActivity1
            // 
            this.faultHandlersActivity1.Activities.Add(this.faultHandlerActivity1);
            this.faultHandlersActivity1.Name = "faultHandlersActivity1";
            // 
            // cancellationHandlerActivity1
            // 
            this.cancellationHandlerActivity1.Name = "cancellationHandlerActivity1";
            // 
            // codeActivity2
            // 
            this.codeActivity2.Name = "codeActivity2";
            this.codeActivity2.ExecuteCode += new System.EventHandler(this.codeActivity2_ExecuteCode);
            // 
            // codeActivity1
            // 
            this.codeActivity1.Name = "codeActivity1";
            this.codeActivity1.ExecuteCode += new System.EventHandler(this.codeActivity1_ExecuteCode);
            // 
            // sequenceActivity1
            // 
            this.sequenceActivity1.Activities.Add(this.codeActivity1);
            this.sequenceActivity1.Activities.Add(this.codeActivity2);
            this.sequenceActivity1.Activities.Add(this.cancellationHandlerActivity1);
            this.sequenceActivity1.Activities.Add(this.faultHandlersActivity1);
            this.sequenceActivity1.Name = "sequenceActivity1";
            // 
            // delayActivity2
            // 
            this.delayActivity2.Name = "delayActivity2";
            this.delayActivity2.TimeoutDuration = System.TimeSpan.Parse("00:00:01");
            this.delayActivity2.InitializeTimeoutDuration += new System.EventHandler(this.delayActivity2_InitializeTimeoutDuration);
            // 
            // whileActivity1
            // 
            this.whileActivity1.Activities.Add(this.sequenceActivity1);
            codecondition1.Condition += new System.EventHandler<System.Workflow.Activities.ConditionalEventArgs>(this.WhileCondition);
            this.whileActivity1.Condition = codecondition1;
            this.whileActivity1.Name = "whileActivity1";
            // 
            // delayActivity1
            // 
            this.delayActivity1.Name = "delayActivity1";
            this.delayActivity1.TimeoutDuration = System.TimeSpan.Parse("00:00:02");
            this.delayActivity1.InitializeTimeoutDuration += new System.EventHandler(this.delayActivity1_InitializeTimeoutDuration);
            // 
            // Workflow1
            // 
            this.Activities.Add(this.delayActivity1);
            this.Activities.Add(this.whileActivity1);
            this.Activities.Add(this.delayActivity2);
            this.Name = "Workflow1";
            this.CanModifyActivities = false;

        }

        #endregion

        private DelayActivity delayActivity2;
        private DelayActivity delayActivity1;
        private WhileActivity whileActivity1;
        private CodeActivity codeActivity2;
        private SequenceActivity sequenceActivity1;
        private FaultHandlersActivity faultHandlersActivity1;
        private CancellationHandlerActivity cancellationHandlerActivity1;
        private FaultHandlerActivity faultHandlerActivity1;
        private CodeActivity codeActivity3;
        private CodeActivity codeActivity1;













    }
}
