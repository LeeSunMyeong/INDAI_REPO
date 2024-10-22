import os


def rename_files_in_directory(directory):
    # Get the name of the parent directory (one level up)
    parent_dir_name = os.path.basename(os.path.normpath(directory))

    for filename in os.listdir(directory):
        path_basename = os.path.basename(parent_dir_name)
        for newFile in os.listdir(filename):
            file_path = os.path.join(directory, newFile)

            # Skip directories
            if os.path.isdir(file_path):
                continue

            # Create the new file name
            new_filename = f"{path_basename}_{newFile}"

            # Construct the full new file path
            new_file_path = os.path.join(directory, new_filename)

            # Rename the file
            os.rename(file_path, new_file_path)
            print(f"Renamed {file_path} to {new_file_path}")



# Example usage
directory = "C:/Users/smmm/Downloads/data/Label/label_Onshore"
rename_files_in_directory(directory)
