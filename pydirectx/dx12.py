import clr
import sys
import os

# Add the local "sharpdx" folder (where the DLLs live)
base_dir = os.path.dirname(os.path.abspath(__file__))
sharpdx_dir = os.path.join(base_dir, "sharpdx")
sys.path.append(sharpdx_dir)

# Load SharpDX assemblies
clr.AddReference("SharpDX")
clr.AddReference("SharpDX.Direct3D12")
clr.AddReference("SharpDX.DXGI")

from SharpDX.Direct3D12 import Device
from SharpDX.DXGI import Factory4


def create_device():
    try:
        # Create a DXGI factory
        factory = Factory4()

        # Get the first adapter (GPU 0)
        adapter = factory.GetAdapter(0)

        # Try to create a D3D12 device on this adapter
        device = Device(adapter)

        if device is None:
            raise ValueError("DirectX 12 not supported on this GPU")

        return device

    except Exception as e:
        raise ValueError("DirectX 12 not supported on this GPU") from e
