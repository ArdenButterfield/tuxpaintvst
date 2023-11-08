import numpy as np
import IPython
import matplotlib.pyplot as plt
from scipy.io import wavfile
from tqdm import tqdm

FILENAME = "/home/arden/testaudio/bellona/kyoto2sec.wav"
fs, data = wavfile.read(FILENAME)
data = data.sum(axis=1).astype(np.single)
data /= max(data)

BASE_WAVE = data
BASE_PERIOD = len(data)
transform = np.fft.fft(BASE_WAVE)
NUM_LINES = BASE_PERIOD // 2 + 1
transform = transform[:NUM_LINES]
mags = abs(transform)
phases = np.angle(transform)
freq_scalars = np.array([i for i in range(NUM_LINES)])
mags[1:-1] *= 2
mags /= BASE_PERIOD

positions = np.ones(len(mags), dtype=np.csingle);
positions *= mags
positions *= np.e ** (1j * phases)
rotations = np.arange(len(positions), dtype=np.single)
rotations /= BASE_PERIOD
rotations *= np.random.normal(loc=1, scale=0.00001, size=rotations.size)
rotations *= np.pi * 2
rotations = np.exp(1j * rotations)
output = []
for i in tqdm(range(10 * fs)):
    positions *= rotations
    output.append(np.sum(positions))
output = np.real(np.array(output))

wavfile.write('rotationout.wav', fs, output)