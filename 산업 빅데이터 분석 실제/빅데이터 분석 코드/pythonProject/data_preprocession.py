# chapter_3_data_preprocessing.py

import pandas as pd

def preprocess_data(file_path):
    data = pd.read_csv(file_path)
    data.fillna(method='ffill', inplace=True)  # 결측치 처리
    return data

if __name__ == "__main__":
    file_path = "data.csv"  # 실제 데이터 파일 경로로 변경
    processed_data = preprocess_data(file_path)
    print(processed_data.head())
