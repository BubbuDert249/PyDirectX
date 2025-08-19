import sys

if sys.platform != "win32":
    raise ValueError("pydirectx only supports Windows")

from . import dx9, dx11, dx12

def version(ver: int):
    if ver == 9:
        try:
            return dx9.create_device()
        except ValueError:
            raise ValueError("DirectX 9 not supported on this GPU")
    elif ver == 11:
        try:
            return dx11.create_device()
        except ValueError:
            raise ValueError("DirectX 11 not supported on this GPU")
    elif ver == 12:
        try:
            return dx12.create_device()
        except ValueError:
            raise ValueError("DirectX 12 not supported on this GPU")
    else:
        raise ValueError("PyDirectX only supports DirectX 9, 11, or 12")
