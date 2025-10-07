#!/usr/bin/env python3
import subprocess
import time
import re
import os
import sys

def run_simulation_test(command, timeout_sec=180):
    """Run simulation with given command and measure time"""
    try:
        start = time.time()
        
        # Prepare input: command + quit
        test_input = f"{command}\nq\n"
        
        # Run simulation
        process = subprocess.Popen(
            ['./build/Simulation'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        stdout, stderr = process.communicate(input=test_input, timeout=timeout_sec)
        elapsed = time.time() - start
        
        # Parse total detections processed
        total_matches = re.findall(r'\[TOTAL\] (\d+)', stdout)
        total_processed = int(total_matches[-1]) if total_matches else 0
        
        # Count detection and pop events
        detection_count = len(re.findall(r'\[DETECTION\]', stdout))
        pop_count = len(re.findall(r'\[POP\]', stdout))
        
        return {
            'elapsed': elapsed,
            'total_processed': total_processed,
            'detections_generated': detection_count,
            'detections_popped': pop_count,
            'stdout': stdout
        }
        
    except subprocess.TimeoutExpired:
        process.kill()
        return None
    except Exception as e:
        print(f"Error running test: {e}")
        return None

def main():
    print("=" * 60)
    print("        Detection Tracking Performance Test")
    print("=" * 60)
    
    # Ensure we're in the right directory
    if not os.path.exists('./build/Simulation'):
        print("Error: ./build/Simulation not found!")
        print("Please run from project root after building.")
        sys.exit(1)
    
    # Create results directory
    os.makedirs('results', exist_ok=True)
    
    # Test configurations - comparing different loads
    tests = [
        ('ten', 10),
        ('hun', 100),
        ('tho', 1000),
        ('ttho', 10000),
    ]
    
    results = []
    
    for command, expected in tests:
        print(f"\n[TEST] Running '{command}' (expected {expected} detections)...")
        result = run_simulation_test(command, timeout_sec=120)
        
        if result:
            avg_latency = (result['elapsed'] / result['total_processed'] * 1000) if result['total_processed'] > 0 else 0
            throughput = result['total_processed'] / result['elapsed'] if result['elapsed'] > 0 else 0
            
            print(f"  ✓ Completed in {result['elapsed']:.2f}s")
            print(f"  ✓ Processed: {result['total_processed']} detections")
            print(f"  ✓ Generated: {result['detections_generated']}")
            print(f"  ✓ Popped: {result['detections_popped']}")
            print(f"  ✓ Avg latency: {avg_latency:.2f}ms per detection")
            print(f"  ✓ Throughput: {throughput:.2f} detections/sec")
            
            results.append({
                'command': command,
                'expected': expected,
                'elapsed': result['elapsed'],
                'processed': result['total_processed'],
                'avg_latency_ms': avg_latency,
                'throughput': throughput
            })
        else:
            print(f"  ✗ Test failed or timed out")
    
    # Generate text report
    report_path = 'results/performance_report.txt'
    with open(report_path, 'w') as f:
        f.write("=" * 60 + "\n")
        f.write("   Detection Tracking Performance Report\n")
        f.write("=" * 60 + "\n\n")
        
        f.write(f"{'Test':<10} {'Detections':<12} {'Time (s)':<12} {'Latency (ms)':<15} {'Throughput':<15}\n")
        f.write("-" * 60 + "\n")
        
        for r in results:
            f.write(f"{r['command']:<10} {r['processed']:<12} {r['elapsed']:<12.2f} {r['avg_latency_ms']:<15.2f} {r['throughput']:<15.2f}\n")
        
        f.write("\n" + "=" * 60 + "\n")
        f.write("Summary Statistics\n")
        f.write("=" * 60 + "\n")
        
        if results:
            avg_latency_overall = sum(r['avg_latency_ms'] for r in results) / len(results)
            avg_throughput = sum(r['throughput'] for r in results) / len(results)
            total_detections = sum(r['processed'] for r in results)
            total_time = sum(r['elapsed'] for r in results)
            
            f.write(f"Total detections processed: {total_detections}\n")
            f.write(f"Total time: {total_time:.2f}s\n")
            f.write(f"Average latency: {avg_latency_overall:.2f}ms\n")
            f.write(f"Average throughput: {avg_throughput:.2f} detections/sec\n")
    
    print(f"\n✓ Report saved to {report_path}")
    
    # Generate CSV for plotting
    csv_path = 'results/performance_metrics.csv'
    with open(csv_path, 'w') as f:
        f.write("test,detections,elapsed_sec,avg_latency_ms,throughput\n")
        for r in results:
            f.write(f"{r['command']},{r['processed']},{r['elapsed']:.3f},{r['avg_latency_ms']:.3f},{r['throughput']:.3f}\n")
    
    print(f"✓ CSV saved to {csv_path}")
    print("\n" + "=" * 60)

if __name__ == '__main__':
    main()