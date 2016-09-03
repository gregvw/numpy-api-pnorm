import numerics
import numpy as np

if __name__ == '__main__':

    p = 2;
    x = np.array([0,1,2])
    value = numerics.norm(x,p)

    print("The " + str(p) + "-norm of the NumPy array x = " \
        + np.str(x) + " is " + str(value))

    
