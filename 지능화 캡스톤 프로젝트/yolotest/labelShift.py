import os

def shift_labels(directory, shift_x=0.10, shift_y=0.10):
    for filename in os.listdir(directory):
        if filename.endswith(".txt"):
            file_path = os.path.join(directory, filename)
            with open(file_path, 'r') as file:
                lines = file.readlines()

            new_lines = []
            for line in lines:
                parts = line.strip().split()
                class_id = parts[0]
                x_center = float(parts[1])
                y_center = float(parts[2])
                width = float(parts[3])
                height = float(parts[4])

                # 오른쪽 하단으로 이동
                x_center = min(x_center + shift_x, 1.0)  # 값이 1.0을 넘지 않도록 함
                y_center = min(y_center + shift_y, 1.0)  # 값이 1.0을 넘지 않도록 함

                new_line = f"{class_id} {x_center:.6f} {y_center:.6f} {width:.6f} {height:.6f}\n"
                new_lines.append(new_line)

            with open(file_path, 'w') as file:
                file.writelines(new_lines)
            print(f"Updated {file_path}")

# 예시 사용
directory = "C:/Users/smmm/Downloads/data/frame/frame_Onboard/val/img"
shift_labels(directory)
