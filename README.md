# PyDirectX
PyDirectX is a wrapper for DirectX 9, 11 and 12 for Python <br>
It combines PythonNet and SharpDX DLLs into one .whl/.tar.gz Python 3 library <br>
# Usage
To run DirectX, you need to specify from pydirectx import dx9 (only dx9, dx11 and dx12, replace dx9 if needed) <br>
You need to run pydirectx.version(dxversion), replace dxversion with 9, 11 or 12, it sets the DirectX version <br>
You need to run DirectX calls to render anything, you also need a HWND <br>
# Troubleshooting
Make sure your OS is Windows 10 or later <br>
Make sure your GPU supports DirectX 9 or later <br>
Make sure you have pythonnet installed <br>
Make sure you have Python 3.7 or later <br>
If the pythonnet installation fails, go to PyPi and download the local .whl <br>
Make sure you create a HWND for the DirectX window <br>
If the .whl doesn't work, install the .tar.gz <br>
If the .tar.gz doesn't work, install the .whl <br>
If both .whl and .tar.gz doesn't work, check the above tips <br>
