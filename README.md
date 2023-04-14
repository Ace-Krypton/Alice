<h1>Alice</h1>
<p align="center">
  <img src="https://user-images.githubusercontent.com/75210504/232134043-69b74b61-2f66-4cfd-920a-4372e0eeb7bc.png" width="30%">
</p>

<p>Alice is an experimental ransomware that uses advanced encryption techniques to protect files. It uses AES-256-CTR in Counter Mode with a random IV for each file, and performs encryption using multithreading for fast and efficient processing.</p>
<h2>Features</h2>
<ul>
    <li>Run in Background (or not) [ - ]</li>
    <li>AES-256-CTR (Counter Mode) with random IV for each file [ + ]</li>
    <li>Multithreading for fast and efficient processing [ - ]</li>
    <li>RSA-4096 for secure client/server communication [ - ]</li>
    <li>Unlocker for decryption of files when needed [ - ]</li>
    <li>Optional TOR Proxy support for additional anonymity [ - ]</li>
    <li>Usage of AES CTR Cipher with stream encryption to avoid loading entire files into memory [ + ]</li>
    <li>Docker image for easy compilation and portability [ - ]</li>
    <li>Daemon or dropper modes for flexibility [ - ]</li>
</ul>
<h2>Compatibility and Configuration Options</h2>
<p>Alice can be compiled using a Docker image, making it easy to build and run on different platforms. Additionally, it can run as a daemon or as a dropper, giving the user the ability to choose the best configuration for their needs.</p>
<h2>Security Considerations</h2>
<p>While Alice utilizes advanced encryption techniques to protect files, it's important to note that no encryption technique is 100% secure. It's recommended to keep encryption keys secure and use additional security measures such as antivirus software and firewalls to protect the system.</p>
<h2>Licensing</h2>
<p>Alice is licensed under the GNU General Public License, allowing it to be open source and free for anyone to use and modify.</p> 
