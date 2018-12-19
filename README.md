# OPTIGA™ Trust X Host Library Integration Guide
 
This application note will serve as a guide on how to integrate and use Infineon's OPTIGA™ Trust X [hostcode library](https://github.com/Infineon/optiga-trust-x) to an application project.

## Introduction

As embedded systems (e.g. IoT devices) are increasingly gaining the attention of attackers, Infineon offers the OPTIGA™ Trust X as a turnkey security solution for industrial automation systems, smart homes, consumer devices and medical devices. This high-end security controller comes with full system integration support for easy and cost-effective deployment of high-end security for your assets.

## Prerequisites

* System Requirements
	* Windows 7/8/10
	* 4GB of RAM or above
	
* Hardware Requirements
	* [XMC2Go™](https://www.infineon.com/cms/de/product/evaluation-boards/kit_xmc_2go_xmc1100_v1/)
	
	![alt text](https://github.com/Infineon/technical-training-optiga-trust-x/blob/master/Images/XMC2Go.PNG)
	* [S2GO SECURITY OPTIGA X](https://www.infineon.com/cms/de/product/security-smart-card-solutions/optiga-embedded-security-solutions/optiga-trust/optiga-trust-x-sls-32aia/)
	
	![alt text](https://github.com/Infineon/technical-training-optiga-trust-x/blob/master/Images/S2Go-TrustX.PNG)
	* 2x 8-PIN Male Headers 
	
	![alt text](https://github.com/Infineon/technical-training-optiga-trust-x/blob/master/Images/8-Pin-Male-Headers.PNG)
	* 2x 8-PIN Female Headers
	
	![alt text](https://github.com/Infineon/technical-training-optiga-trust-x/blob/master/Images/8-Pin-Female-Headers.PNG)
	* Micro USB Cable
	
* Software Requirements
	* [OPTIGA™ TrustX Host Library](https://github.com/Infineon/optiga-trust-x)
	* [Dave™4.4.2](https://infineoncommunity.com/dave-download_ID645)
	* [PuTTY SSH and Telnet Clien](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html)
	

## Getting Started

To get started you can follow the step-by-step instructions provided in [Optiga_TrustX_Integration_Manual_vX.X.pdf](https://github.com/Infineon/technical-training-optiga-trust-x/tree/master/Docs)

To clone project in to your local hard drive use "--recursive" option. This will clone the OPTIGA™ TrustX Host Library that is added as a submodule into your project as well.

Example:
git clone --recursive https://github.com/Infineon/technical-training-optiga-trust-x.git

## License

The MIT License

Copyright (c) 2018 Infineon Technologies AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE	

