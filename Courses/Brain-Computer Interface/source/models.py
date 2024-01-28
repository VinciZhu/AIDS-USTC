import tensorflow as tf
from keras import Model, Sequential
from keras.layers import (
    Dense,
    Conv1D,
    Conv2D,
    AveragePooling1D,
    AveragePooling2D,
    Dropout,
)


class NovelCNN(Model):
    def __init__(self, n_blocks=7, base_ch=32, out_dim=512, dropout=0.5):
        super().__init__()
        self.n_blocks = n_blocks
        self.out_dim = out_dim
        self.blocks = []
        for i in range(n_blocks):
            layers = [
                Conv1D(
                    filters=base_ch * 2**i,
                    kernel_size=3,
                    padding='same',
                    activation='relu',
                    kernel_initializer='he_normal',
                    name='conv1',
                ),
                Conv1D(
                    filters=base_ch * 2**i,
                    kernel_size=3,
                    padding='same',
                    activation='relu',
                    kernel_initializer='he_normal',
                    name='conv2',
                ),
            ]
            if i > 2:
                layers.append(Dropout(dropout, name='dropout'))
            if i < n_blocks - 1:
                layers.append(AveragePooling1D(pool_size=2, name='pool'))
            block = Sequential(layers, name=f'block{i}')
            self.blocks.append(block)
        self.fc = Dense(out_dim, name='fc')

    def call(self, x):
        x = tf.expand_dims(x, axis=-1)
        for i in range(self.n_blocks):
            x = self.blocks[i](x)
        x = tf.reshape(x, (-1, x.shape[1] * x.shape[2]))
        x = self.fc(x)
        return x


class SpecNovelCNN(Model):
    def __init__(
        self,
        window_sizes=[16, 32, 64, 128],
        spec_ch=4,
        n_blocks=7,
        base_ch=32,
        out_dim=512,
        dropout=0.5,
    ):
        super().__init__()
        self.window_sizes = window_sizes
        self.n_blocks = n_blocks
        self.out_dim = out_dim

        self.blocks = []
        for i in range(n_blocks):
            layers = [
                Conv1D(
                    filters=base_ch * 2**i,
                    kernel_size=3,
                    padding='same',
                    activation='relu',
                    kernel_initializer='he_normal',
                    name='conv1',
                ),
                Conv1D(
                    filters=base_ch * 2**i,
                    kernel_size=3,
                    padding='same',
                    activation='relu',
                    kernel_initializer='he_normal',
                    name='conv2',
                ),
            ]
            if i > 2:
                layers.append(Dropout(dropout, name='dropout'))
            if i < n_blocks - 1:
                layers.append(AveragePooling1D(pool_size=2, name='pool'))
            block = Sequential(layers, name=f'block{i}')
            self.blocks.append(block)

        self.spec_blocks = []
        for i in range(n_blocks - 4):
            layers = [
                Conv2D(
                    filters=spec_ch,
                    kernel_size=3,
                    padding='same',
                    activation='relu',
                    kernel_initializer='he_normal',
                    name='conv1',
                ),
                Conv2D(
                    filters=spec_ch,
                    kernel_size=3,
                    padding='same',
                    activation='relu',
                    kernel_initializer='he_normal',
                    name='conv2',
                ),
                Dropout(dropout, name='dropout'),
                AveragePooling2D(pool_size=2, name='pool'),
            ]
            block = Sequential(layers, name=f'spec_block{i}')
            self.spec_blocks.append(block)

        self.fc = Dense(out_dim, name='fc')

    def call(self, x):
        specs = []
        initial_dim = self.out_dim // 2**3
        for ws in self.window_sizes:
            spec = tf.signal.stft(x, ws, ws // 2)  # (B, T, F)
            spec = tf.expand_dims(spec, axis=-1)  # (B, T, F, C)
            spec = tf.image.resize(tf.abs(spec), (initial_dim, initial_dim))
            specs.append(spec)
        s = tf.concat(specs, axis=-1)
        x = tf.expand_dims(x, axis=-1)
        for i in range(self.n_blocks):
            x = self.blocks[i](x)
            if i > 2 and i < self.n_blocks - 1:
                s = self.spec_blocks[i - 3](s)
                s_ = tf.reshape(
                    s, (-1, s.shape[1], s.shape[2] * s.shape[3])
                )  # (B, T, F*C)
                x = tf.concat([x, s_], axis=-1)
        x = tf.reshape(x, (-1, x.shape[1] * x.shape[2]))
        x = self.fc(x)
        return x
