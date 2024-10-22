# chapter_5_data_visualization.py

import pandas as pd
import matplotlib.pyplot as plt

def visualize_data(data):
    plt.figure(figsize=(10, 6))
    data['column_name'].hist(bins=30)  # 특정 열의 히스토그램
    plt.title("Data Distribution")
    plt.xlabel("Values")
    plt.ylabel("Frequency")
    plt.show()

if __name__ == "__main__":
    data = pd.read_csv("processed_data.csv")  # 전처리된 데이터 파일 경로로 변경
    visualize_data(data)
