# ZeroTrace

**Secure Data Wiping for Trustworthy IT Asset Recycling**

ZeroTrace is a high-performance, bootable USB utility designed to securely sanitize storage devices for safe reuse or recycling. It operates below the operating system level and complies with **NIST SP 800-88** media sanitization standards, ensuring data is permanently unrecoverable and **cryptographically verifiable via blockchain**.

---

## Limitless Trust through Verification

ZeroTrace doesn't just wipe data; it provides cryptographic proof. Every successful wipe generates a digital **Certificate of Destruction** which is anchored to the **Ethereum blockchain**, allowing anyone to verify the sanitization status of a device using its unique Certificate ID.

---

## Problem Statement

- Over **1.75 million tonnes of e-waste** are generated annually in India.
- ₹50,000+ crore worth of unused devices remain idle due to **data privacy fears**.
- Users lack:
  - Reliable data destruction methods
  - Tamper-proof proof of sanitization
  - Trust in recycling vendors

---

## Solution Overview

ZeroTrace provides a **low-level, OS-independent disk sanitization tool** that:

- Securely wipes storage devices using industry-approved methods
- Generates **tamper-proof Certificates of Destruction**
- Stores verification records on **Ethereum blockchain**
- Enables public, third-party verification of wipe status

---

## Key Features

### 🔐 NIST-Compliant Data Sanitization
- Firmware-level erase (ATA Secure Erase / NVMe Format)
- Cryptographic erase for self-encrypted drives
- Multi-pass overwrite for non-encrypted drives

### 💻 Cross-Platform Bootable Utility
- Works on **Windows, Linux, Android**
- Compatible with SATA, NVMe, USB, eMMC
- Bypasses OS-level and filesystem restrictions

### ⛓️ Blockchain-Verified Certification
- Certificates stored on **IPFS**
- Verification hashes anchored on **Ethereum**
- Immutable, tamper-proof wipe proof

### 🎯 Designed for All Users
- One-click, intuitive interface
- Free for individuals, scalable for enterprises
- **Instant Verification**: Verify any certificate directly from the home screen using the Certificate ID.

---

## Technical Architecture

### ZeroTrace Core (C++)
The bootable agent responsible for hardware interaction.
- **Boot & Discovery**: Enumerates all attached storage devices.
- **Wipe Engine**:Executes `hdparm`, `nvme-cli`, or direct I/O overwrite commands.
- **Certificate Generator**: Creates a JSON certificate with device metadata and wipe timestamps.

### ZT-Chain Helper (Node.js)
A bridge service handling blockchain interactions.
- Receives certificate hashes from the Core.
- Interacts with the **Ethereum Smart Contract**.
- Exposes API endpoints for recording and verifying wipes.

### Smart Contract (Solidity)
The immutable registry of wiped devices.
- Stores mapping of `CertificateHash -> (DeviceHash, Timestamp, Method)`.
- Allows public verification without revealing sensitive user data.

---

## Step-by-Step Workflow

### 1. Launch & Discovery
Upon booting ZeroTrace, the application automatically scans for all connected storage devices (HDD, SSD, NVMe, USB).

The **Home Screen** displays:
- A list of all detected devices with their details (Model, Size, Serial).
- **Verify Certificate Option**: A prominent feature on the dashboard allowing users to input a Certificate ID to instantly verify a past wipe.

![Home Screen - Device List & Verify Option](docs/images/zerotrace_device_list_placeholder.png)
*(Screenshot of the main dashboard showing device list and the 'Verify Certificate' button)*

### 2. Select a Device
Click on any device card to view detailed information and proceed to the wiping options. ZeroTrace identifies if the drive is an SSD, HDD, or removable media.

### 3. Choose Wipe Method
Select the most appropriate sanitization method for your needs:
- **ATA Secure Erase**: (Recommended for SSDs) Fast, built-in firmware erasure.
- **Cryptographic Erase**: (For SEDs) Instantly destroys the encryption key.
- **Plain Overwrite**: (For HDDs/USB) Writes zeros or random patterns across the entire disk.

![Wipe Options Screen](docs/images/zerotrace_wipe_options_placeholder.png)
*(Screenshot of the wipe method selection screen)*

### 4. Confirm & Execute
Click **"PERFORM WIPE"**. A final warning will appear as this action is irreversible. The progress bar will indicate the status of the operation.

### 5. Success & Certification
Once completed, a **Certificate of Destruction** is generated. The app automatically communicates with the blockchain node (if online) to register the wipe. You will see a "Success" screen with the Certificate ID.

![Success Screen](docs/images/zerotrace_success_placeholder.png)
*(Screenshot showing successful wipe and generated certificate)*

### 6. Verify a Certificate
To verify a device's sanitization status:
1. Navigate to the **Home Screen**.
2. Click **"Verify Certificate"**.
3. Enter the **Certificate ID** (from the success screen or printed report).
4. The system queries the blockchain and returns the wipe record (Device Model, Date, Method) if valid.

---

## Developer Guide

### Prerequisites
- **C++ Build Tools**: `cmake`, `g++`, `gtk4-dev`
- **Node.js**: `v16+` & `npm`
- **Hardhat**: For smart contract deployment

### Building Core (zt-client)
```bash
cd zt-client
mkdir build && cd build
cmake ..
make
./ZeroTraceClient
```

### Running Blockchain Node (zt-chain)
```bash
cd zt-chain
npm install
# Ensure local hardhat node is running or configure .env for Testnet
node index.js
```

### Smart Contracts (zt-verify)
```bash
cd zt-verify
npm install
npx hardhat node  # Runs local Ethereum node
npx hardhat run scripts/deploy.js --network localhost
```

---

