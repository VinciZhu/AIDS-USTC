import numpy as np
import tensorflow as tf
from sklearn.model_selection import train_test_split


def seed_everything(seed=0):
    np.random.seed(seed)
    tf.random.set_seed(seed)


def synthesize_signal(x, n, snr):
    x_energy = np.sum(x**2, axis=-1, keepdims=True)
    n_energy = np.sum(n**2, axis=-1, keepdims=True)
    lamda = np.sqrt(x_energy / n_energy) / (10 ** (snr / 20))
    return x + lamda * n


def batch_generator(eegs, emgs, batch_size, min_snr=-5, max_snr=5):
    while True:
        eeg_idx = np.random.choice(eegs.shape[0], batch_size)
        emg_idx = np.random.choice(emgs.shape[0], batch_size)
        x, n = eegs[eeg_idx], emgs[emg_idx]
        snr = np.random.uniform(min_snr, max_snr, (batch_size, 1))
        y = synthesize_signal(x, n, snr)
        std = np.std(y, axis=-1, keepdims=True)
        y = y / std
        x = x / std
        yield y, x


def create_eval_data(eegs, emgs, eval_size, min_snr=-5, max_snr=5):
    eeg_idx = np.repeat(np.arange(eegs.shape[0]), np.ceil(eval_size / eegs.shape[0]))
    eeg_idx = np.random.permutation(eeg_idx)[:eval_size]
    emg_idx = np.repeat(np.arange(emgs.shape[0]), np.ceil(eval_size / emgs.shape[0]))
    emg_idx = np.random.permutation(emg_idx)[:eval_size]
    x, n = eegs[eeg_idx], emgs[emg_idx]
    snr = np.random.uniform(min_snr, max_snr, (eval_size, 1))
    y = synthesize_signal(x, n, snr)
    std = np.std(y, axis=-1, keepdims=True)
    y = y / std
    x = x / std
    return (y, x), std


def prepare_data(data_dir, batch_size=256, seed=0, verbose=False):
    all_eegs = np.load(f'{data_dir}/EEG_all_epochs.npy')
    all_emgs = np.load(f'{data_dir}/EMG_all_epochs.npy')

    seed_everything(seed)

    # split data into train, val, test by 70:10:20
    train_eegs, test_eegs = train_test_split(all_eegs, test_size=0.2)
    train_emgs, test_emgs = train_test_split(all_emgs, test_size=0.2)
    train_eegs, val_eegs = train_test_split(train_eegs, test_size=0.125)
    train_emgs, val_emgs = train_test_split(train_emgs, test_size=0.125)

    if verbose:
        print('EEG in training set:  ', train_eegs.shape)
        print('EMG in training set:  ', train_emgs.shape)
        print('EEG in validation set:', val_eegs.shape)
        print('EMG in validation set:', val_emgs.shape)
        print('EEG in test set:      ', test_eegs.shape)
        print('EMG in test set:      ', test_emgs.shape)

    train_generator = batch_generator(train_eegs, train_emgs, batch_size)
    train_dataset = tf.data.Dataset.from_generator(
        lambda: train_generator,
        output_types=(tf.float32, tf.float32),
        output_shapes=(
            tf.TensorShape((batch_size, 512)),
            tf.TensorShape((batch_size, 512)),
        ),
    )

    seed_everything(seed)

    val_size = max(val_eegs.shape[0], val_emgs.shape[0]) * 5
    test_size = max(test_eegs.shape[0], test_emgs.shape[0]) * 5
    val_data, _ = create_eval_data(val_eegs, val_emgs, val_size)
    test_data, test_std = create_eval_data(test_eegs, test_emgs, test_size)
    val_dataset = tf.data.Dataset.from_tensor_slices(val_data).batch(batch_size)
    test_dataset = tf.data.Dataset.from_tensor_slices(test_data).batch(batch_size)

    if verbose:
        print('val_size:', val_size)
        print('test_size:', test_size)

    return train_dataset, val_dataset, test_dataset, test_std
