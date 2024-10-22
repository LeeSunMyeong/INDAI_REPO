from ultralytics import YOLO
import torch

print(f"CUDA available: {torch.cuda.is_available()}")

# 현재 CUDA 장치 확인
if torch.cuda.is_available():
    print(f"Current CUDA device: {torch.cuda.current_device()}")
    print(f"CUDA device name: {torch.cuda.get_device_name(torch.cuda.current_device())}")
else:
    print("CUDA is not available.")

# # YOLOv8 모델 로드
# model = YOLO('yolov8s.pt')  # YOLOv8n pre-trained weights 사용
#
# # 데이터셋 설정 파일 경로
# data_yaml = 'path/to/your/data.yaml'  # data.yaml 파일 경로 설정
#
# # 모델 학습
# model.train(data=data_yaml, epochs=50, batch=8, imgsz=640, device=0)  # device=0 설정
#
# # 모델 평가
# model.val(data=data_yaml, imgsz=640, device=0)  # device=0 설정