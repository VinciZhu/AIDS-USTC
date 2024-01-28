import tensorflow as tf
from keras.metrics import Metric


# correlation coefficient
class CC(Metric):
    def __init__(self, name='cc', **kwargs):
        super().__init__(name=name, **kwargs)
        self.cc = self.add_weight(name='cc', initializer='zeros')

    def update_state(self, y_true, y_pred, sample_weight=None):
        y_true = y_true - tf.reduce_mean(y_true, axis=-1, keepdims=True)
        y_pred = y_pred - tf.reduce_mean(y_pred, axis=-1, keepdims=True)
        y_true = tf.nn.l2_normalize(y_true, axis=-1)
        y_pred = tf.nn.l2_normalize(y_pred, axis=-1)
        cc = tf.reduce_mean(tf.reduce_sum(y_true * y_pred, axis=-1))
        self.cc.assign(cc)

    def result(self):
        return self.cc

    def reset_state(self):
        self.cc.assign(0.0)


# relative root mean squared error
class RRMSE(Metric):
    def __init__(self, name='rrmse', **kwargs):
        super().__init__(name=name, **kwargs)
        self.rrmse = self.add_weight(name='rrmse', initializer='zeros')

    def update_state(self, y_true, y_pred, sample_weight=None):
        noise = y_true - y_pred
        y_norm = tf.norm(y_true, axis=-1)
        n_norm = tf.norm(noise, axis=-1)
        rrmse = n_norm / y_norm
        self.rrmse.assign(tf.reduce_mean(rrmse))

    def result(self):
        return self.rrmse

    def reset_state(self):
        self.rrmse.assign(0.0)


# signal-to-noise ratio
class SNR(Metric):
    def __init__(self, name='snr', **kwargs):
        super().__init__(name=name, **kwargs)
        self.snr = self.add_weight(name='snr', initializer='zeros')

    def update_state(self, y_true, y_pred, sample_weight=None):
        noise = y_true - y_pred
        y_energy = tf.reduce_mean(y_true**2, axis=-1)
        n_energy = tf.reduce_mean(noise**2, axis=-1)
        snr = 10 * tf.math.log(y_energy / n_energy) / tf.math.log(10.0)
        self.snr.assign(tf.reduce_mean(snr))

    def result(self):
        return self.snr

    def reset_state(self):
        self.snr.assign(0.0)
