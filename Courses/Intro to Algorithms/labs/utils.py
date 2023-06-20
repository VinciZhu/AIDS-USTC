import os
import random
import shutil
import requests
from tqdm import tqdm
from typing import Dict, Any
from types import SimpleNamespace

import numpy as np
import tensorflow as tf
from tqdm import tqdm

try:
    import tomllib  # type: ignore
except ModuleNotFoundError:
    import tomli as tomllib  # type: ignore


def seed_everything(seed=42):
    random.seed(seed)
    os.environ['PYTHONHASHSEED'] = str(seed)
    np.random.seed(seed)
    tf.random.set_seed(seed)


def download_file(url, out_path, exist_ok=False, rewrite=False):
    if os.path.exists(out_path):
        if exist_ok:
            return
        elif rewrite:
            os.remove(out_path)
        else:
            raise RuntimeError(f'File {out_path} already exists')

    res = requests.get(url, stream=True)
    total_size = int(res.headers.get('content-length', 0))
    with open(out_path, 'wb') as file:
        with tqdm(
            desc=url.split('/')[-1], total=total_size, unit='iB', unit_scale=True
        ) as pbar:
            for data in res.iter_content(1024):
                pbar.update(len(data))
                file.write(data)

    if total_size != 0 and pbar.n != total_size:
        os.remove(out_path)
        raise RuntimeError(f'Error while downloading {url}')


def download_files(urls, out_dir, exist_ok=False, rewrite=False):
    os.makedirs(out_dir, exist_ok=True)
    for url in urls:
        out_path = os.path.join(out_dir, url.split('/')[-1])
        download_file(url, out_path, exist_ok=exist_ok, rewrite=rewrite)


def extract_file(zip_file, out_dir, remove=False):
    shutil.unpack_archive(zip_file, out_dir)
    if remove:
        os.remove(zip_file)


def move_content(src_dir, dst_dir, remove=False):
    for file in os.listdir(src_dir):
        shutil.move(os.path.join(src_dir, file), dst_dir)
    if remove:
        os.rmdir(src_dir)


def read_toml(path) -> Dict[str, Any]:
    with open(path, 'rb') as file:
        return tomllib.load(file)


def parse_toml(toml) -> Dict[str, Any]:
    return tomllib.loads(toml)


def dict_to_namespace(d: Dict[str, Any]) -> SimpleNamespace:
    ns = SimpleNamespace()
    for k, v in d.items():
        if isinstance(v, dict):
            v = dict_to_namespace(v)
        setattr(ns, k, v)
    return ns


def namespace_to_dict(ns: SimpleNamespace) -> Dict[str, Any]:
    d = {}
    for k, v in vars(ns).items():
        if isinstance(v, SimpleNamespace):
            v = namespace_to_dict(v)
        d[k] = v
    return d
