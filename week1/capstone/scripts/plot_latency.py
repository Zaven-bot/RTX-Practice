#!/usr/bin/env python3
import matplotlib
matplotlib.use('Agg')  # Use non-interactive backend for Jenkins
import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

def main():
    try:
        if not os.path.exists('results/performance_metrics.csv'):
            print("Error: performance_metrics.csv not found!")
            print("Run perf_test.py first.")
            sys.exit(1)
        
        df = pd.read_csv('results/performance_metrics.csv')
        
        # Create figure with 2x2 subplots for comprehensive comparison
        fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
        
        # 1. Latency vs Number of Detections
        ax1.plot(df['detections'], df['avg_latency_ms'], 
                marker='o', linewidth=2.5, markersize=10, color='#2E86AB', label='Avg Latency')
        ax1.set_xlabel('Number of Detections', fontsize=13, fontweight='bold')
        ax1.set_ylabel('Average Latency (ms)', fontsize=13, fontweight='bold')
        ax1.set_title('Detection Processing Latency', fontsize=15, fontweight='bold', pad=15)
        ax1.grid(True, alpha=0.3, linestyle='--')
        ax1.set_xscale('log')
        ax1.legend(fontsize=11)
        
        # Add value labels on points
        for i, row in df.iterrows():
            ax1.annotate(f'{row["avg_latency_ms"]:.1f}ms', 
                        xy=(row['detections'], row['avg_latency_ms']),
                        xytext=(5, 5), textcoords='offset points', fontsize=9)
        
        # 2. Throughput vs Number of Detections
        ax2.plot(df['detections'], df['throughput'], 
                marker='s', linewidth=2.5, markersize=10, color='#06A77D', label='Throughput')
        ax2.set_xlabel('Number of Detections', fontsize=13, fontweight='bold')
        ax2.set_ylabel('Throughput (detections/sec)', fontsize=13, fontweight='bold')
        ax2.set_title('Detection Processing Throughput', fontsize=15, fontweight='bold', pad=15)
        ax2.grid(True, alpha=0.3, linestyle='--')
        ax2.set_xscale('log')
        ax2.legend(fontsize=11)
        
        # Add value labels
        for i, row in df.iterrows():
            ax2.annotate(f'{row["throughput"]:.1f}/s', 
                        xy=(row['detections'], row['throughput']),
                        xytext=(5, 5), textcoords='offset points', fontsize=9)
        
        # 3. Total Processing Time
        ax3.bar(df['test'], df['elapsed_sec'], color=['#A23B72', '#F18F01', '#C73E1D', '#6A994E'], 
                edgecolor='black', linewidth=1.5)
        ax3.set_xlabel('Test Case', fontsize=13, fontweight='bold')
        ax3.set_ylabel('Total Time (seconds)', fontsize=13, fontweight='bold')
        ax3.set_title('Total Processing Time by Test', fontsize=15, fontweight='bold', pad=15)
        ax3.grid(True, alpha=0.3, axis='y', linestyle='--')
        
        # Add value labels on bars
        for i, (test, val) in enumerate(zip(df['test'], df['elapsed_sec'])):
            ax3.text(i, val + 0.5, f'{val:.2f}s', ha='center', fontsize=10, fontweight='bold')
        
        # 4. Comparison Table
        ax4.axis('tight')
        ax4.axis('off')
        
        table_data = []
        table_data.append(['Test', 'Detections', 'Time (s)', 'Latency (ms)', 'Throughput'])
        for _, row in df.iterrows():
            table_data.append([
                row['test'],
                f"{int(row['detections'])}",
                f"{row['elapsed_sec']:.2f}",
                f"{row['avg_latency_ms']:.2f}",
                f"{row['throughput']:.1f}"
            ])
        
        table = ax4.table(cellText=table_data, cellLoc='center', loc='center',
                         colWidths=[0.15, 0.2, 0.2, 0.2, 0.25])
        table.auto_set_font_size(False)
        table.set_fontsize(11)
        table.scale(1, 2.5)
        
        # Style header row
        for i in range(5):
            table[(0, i)].set_facecolor('#2E86AB')
            table[(0, i)].set_text_props(weight='bold', color='white')
        
        # Alternate row colors
        for i in range(1, len(table_data)):
            for j in range(5):
                if i % 2 == 0:
                    table[(i, j)].set_facecolor('#E8E8E8')
        
        ax4.set_title('Performance Summary Table', fontsize=15, fontweight='bold', pad=20)
        
        plt.suptitle('Detection Tracking System - Performance Analysis', 
                    fontsize=18, fontweight='bold', y=0.98)
        
        plt.tight_layout(rect=[0, 0, 1, 0.96])
        
        output_path = 'results/latency_report.png'
        plt.savefig(output_path, dpi=200, bbox_inches='tight')
        print(f"✓ Plot saved to {output_path}")
        
    except ImportError as e:
        print(f"Error: Missing required library: {e}")
        print("Install with: pip3 install matplotlib pandas")
        sys.exit(1)
    except Exception as e:
        print(f"Error generating plot: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == '__main__':
    main()