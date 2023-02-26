Corpse - Ransomware

Corpse is an experimental ransomware that uses advanced encryption techniques to encrypt your files. 
With Corpse, you can encrypt your files with AES-256-CTR in Counter Mode, using a random IV for each file. 
The encryption is performed using multithreading, which ensures fast and efficient processing.
Corpse also uses RSA-4096 to secure the client/server communication, providing an extra layer of protection. 
The included Unlocker allows you to decrypt your files when you need to access them, and an optional TOR Proxy support provides additional anonymity.
To avoid loading an entire file into memory, Corpse uses an AES CTR Cypher with stream encryption. 
This technique allows for fast encryption and decryption of large files without the need to load them entirely into memory.
Corpse can be compiled using a Docker image, making it easy to build and run on different platforms. 
Additionally, it can run as a daemon or as a dropper, allowing you to choose the best configuration for your needs.


Features

    Run in Background (or not)
    AES-256-CTR(Counter Mode) with random IV for each file
    Multithreading
    RSA-4096 to secure the client/server communication
    Include an Unlocker
    Optional TOR Proxy support
    Usege of AES CTR Cypher with stream encryption to avoid load an entire file into memory
    Docker image for compilation
    Daemon
    Dropper


Security

Corpse uses advanced encryption techniques to protect your files. 
However, no encryption technique is 100% secure, and Corpse is no exception. 
It is important to keep your encryption key secure and to use other security measures, such as antivirus software and firewalls, to protect your system.


License

Corpse is licensed under the MIT License. See the LICENSE file for more information.
