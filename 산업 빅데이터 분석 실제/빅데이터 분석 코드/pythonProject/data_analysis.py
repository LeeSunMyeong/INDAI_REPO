# chapter_4_data_analysis.py

import pandas as pd

def analyze_data(data):
    summary = data.describe()  # 데이터 요약 통계
    return summary

if __name__ == "__main__":
    data = pd.read_csv("processed_data.csv")  # 전처리된 데이터 파일 경로로 변경
    summary_stats = analyze_data(data)
    print(summary_stats)
