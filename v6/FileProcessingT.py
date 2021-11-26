# -------------------------------------------------------------------------------------------------
# The FileProcessingT.py module is created for organsizing file processing tools. Currently there 
# is only save_with_backup method exist.
# -------------------------------------------------------------------------------------------------

import os
import numpy as np

def save_with_backup(file_dir, array):
    """
    This function will save numpy array using numpy.savetxt while keeping backup with extension '.bck'.
    """
    i=0
    while i >= 0:
        if os.path.exists(file_dir):
            if os.path.exists(file_dir+".bck{}".format(i)):
                i+=1
                continue
            else:
                os.rename(os.path.realpath(file_dir), os.path.realpath(file_dir)+".bck{}".format(i))
                print("Attention: File with name '{}' already exists. New backup file '{}' has been created!".format(file_dir, file_dir+'.bck{}'.format(i)))
                break
        else:
            print("No file named '{}' exist. Will save a new one now.".format(file_dir))
            break
    
    np.savetxt(file_dir, array)
    print('File has been saved successfully.')
    
    return None