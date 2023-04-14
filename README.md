<h1>Alice</h1>
<p>Alice is an experimental ransomware that utilizes advanced encryption techniques to encrypt files. With this ransomware, files can be encrypted using AES-256-CTR in Counter Mode with a random IV for each file. The encryption is performed using multithreading, ensuring fast and efficient processing.</p>
<h2>Features</h2>
<ul>
    <li>Run in Background (or not)</li>
    <li>AES-256-CTR(Counter Mode) with random IV for each file</li>
    <li>Multithreading</li>
    <li>RSA-4096 to secure the client/server communication</li>
    <li>Include an Unlocker</li>
    <li>Optional TOR Proxy support</li>
    <li>Usage of AES CTR Cypher with stream encryption to avoid load an entire file into memory</li>
    <li>Docker image for compilation</li>
    <li>Daemon</li>
    <li>Dropper</li>
</ul>
<p>RSA-4096 is used to secure the client/server communication, adding an extra layer of protection. It includes an Unlocker that allows for decryption of files when needed, and optional TOR Proxy support provides additional anonymity.</p>
<p>To avoid loading an entire file into memory, it uses an AES CTR Cipher with stream encryption, enabling fast encryption and decryption of large files without the need to load them entirely into memory.</p>
<p>It can be compiled using a Docker image, making it easy to build and run on different platforms. Additionally, it can run as a daemon or as a dropper, giving the user the ability to choose the best configuration for their needs.</p>
<p>While it utilizes advanced encryption techniques to protect files, it is important to note that no encryption technique is 100% secure. Keeping encryption keys secure and using additional security measures such as antivirus software and firewalls is recommended to protect the system.</p>
<p>It is licensed under the MIT License, allowing for it to be open source and free for anyone to use and modify.</p>
