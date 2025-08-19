import pydx12

def create_device():
    try:
        # Attempt to create a DX12 device on the primary adapter (GPU 0)
        device = pydx12.Device.create()
        if device is None:
            raise ValueError("DirectX 12 not supported on this GPU")
        return device
    except Exception as e:
        raise ValueError("DirectX 12 not supported on this GPU") from e
