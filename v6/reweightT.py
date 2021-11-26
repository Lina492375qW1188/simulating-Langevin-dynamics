# -------------------------------------------------------------------------------------------------
# This class is used to compute e^(beta*Vbias), e^(beta*c), and reweighting array for metadynamics
# results from the simulation of Langevin dynamics performed using my CPP program.
# -------------------------------------------------------------------------------------------------

import numpy as np
from FileProcessingT import save_with_backup

class reweight:
    
    def __init__(self, s, beta, hbias, sbias, wbias, bias_factor, stride, ds=0.5, rescale=False):
        
        # Trajectory
        self.s = s
        self.beta = beta # beta=1/kB/T, where kB=Boltzmann constant, T=temperature
        
        # Bias potential
        self.hbias = hbias
        self.sbias = sbias
        self.wbias = wbias
        self.bias_factor = bias_factor # The gamma factor in metaD.
        self.stride = stride # ratio of updating frequency between s and sbias.
        
        # Exponents
        self.exp_num = bias_factor/(bias_factor-1)
        self.exp_den = 1/(bias_factor-1)
        
        # Integration
        self.ds = ds # Interval used for integration
        
        # Rescale Gaussian bias or not ## Haven't implement this part yet.
        self.rescale = rescale 
        
        # Output
        self.rw_arr=np.zeros(self.s.shape[0])

        
    def exp_beta_Vbias(self, s_t, nline, hbias_t, sbias_t):
        """
        exp(beta*Vbias) # nline is t in unit of lines.
        Number of hbias and sbias should less than or equal to nline.
        """
        if nline<len(hbias_t) or nline<len(sbias_t): 
            raise TypeError
        
        Vbias_t = np.sum(hbias_t*np.exp(-0.5*(s_t-sbias_t)**2/self.wbias**2))
        
        return np.exp(self.beta*Vbias_t)

    
    def exp_beta_c(self, nline, hbias_t, sbias_t):
        """
        exp(beta*c[nline]) # nline is t in unit of lines.
        Number of hbias and sbias should less than or equal to nline.
        """
        # if the following statement is not true, the causality breaks.
        if nline<len(hbias_t) or nline<len(sbias_t): 
            raise ValueError
        
        # nline=0 is the initial configuration. Without this line, the following sb_max/sb_min break.
        if nline==0: return 1
        
        sb_max=np.max(sbias_t)+3*self.ds # Upper bound
        sb_min=np.min(sbias_t)-3*self.ds # Lower bound
        
        s_range = np.arange(sb_min, sb_max, self.ds)
        arr=np.array([self.exp_beta_Vbias(ss, nline, hbias_t, sbias_t) for ss in s_range])
        
        num=np.sum(arr**self.exp_num)
        den=np.sum(arr**self.exp_den)
    
        return num/den
    

    def compute(self, file_dir=False):
        """
        Compute reweighting factor. file_dir: The directory and name of output file.
        """
        for t, s_t in enumerate(self.s):
            
            sbias_t=self.sbias[:t:self.stride]
            hbias_t=self.hbias[:t:self.stride]
                
            self.rw_arr[t]=self.exp_beta_Vbias(s_t, t, hbias_t, sbias_t)/self.exp_beta_c(t, hbias_t, sbias_t)
            
        if file_dir:
            save_with_backup(file_dir, self.rw_arr)
            return None
        else:
            return self.rw_arr

        
if __name__ == "__main__":
    
    # Read biased data:
    biased_x, biased_y, hbias, xbias, ybias = np.loadtxt(biased_traj, unpack=True, usecols=(0,1,6,7,8), skiprows=1)
    
    start = time.time()
    # Parameters:
    coefficient = (0.891, 0.454) # RC = 0.891*x + 0.454*y is used to perform 1-dim metadynamics here.
    stride=200
    stride = stride//Rout # (unit: lines), stride = 1000 steps
    wbias = 0.2
    delta_beta = 0.01
    ds=0.2

    # Define bias factor
    T, dT = 1/beta, 1/delta_beta
    bias_factor = (T+dT)/T

    # Data:
    s = coefficient[0]*biased_x + coefficient[1]*biased_y
    sbias = coefficient[0]*xbias + coefficient[1]*ybias

    # Create rw
    rw = reweightT.reweight(s, beta, hbias, sbias, wbias, bias_factor, stride, ds)

    # Compute weights
    weights = rw.compute()

    print(time.time()-start, 's')
