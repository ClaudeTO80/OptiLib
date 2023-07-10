/*!
   \file ng_stl.cpp
   \author Philippose Rajan
   \date 14 Feb 2009 (Created)

   This sample utility demonstrates the use of the Netgen
   nglib library for reading, and meshing an STL geometry.

   The Program takes as input the name of an STL file
   saved in the STL ASCII Format, and generates a 3D Volume
   mesh which is saved into the file "test.vol".

   test.vol can be viewed using the usual Netgen Mesher GUI
*/

#include <stdio.h>
#include <stdlib.h>
#include "Bounds.h"
#include "Value.h"
#include "ValueFactory.h"
#include "ElementSet.h"
#include "DesignSet.h"
#include "Model.h"
#include "Poco/FileStream.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CipherKey.h"
#include "Poco/Crypto/EVPPKey.h"
#include "Poco/Crypto/EVPCipherImpl.h"
#include "Poco/Crypto/CipherFactory.h"
#include "Poco/Crypto/CryptoStream.h"

using namespace Poco::Crypto;
int main()
{
    CipherFactory& factory = CipherFactory::defaultFactory();
    // Creates a 256-bit AES cipher

    EVPPKey EVPKey=EVPPKey(
                        R"(C:\PortableProgs\putty\Data\public.pem)", //const std::string & publicKeyFile,
                        R"(C:\PortableProgs\putty\Data\private.ppk)", //const std::string & privateKeyFile,
                        "password" //const std::string & privateKeyPassphrase = ""
                    );
    
    //Cipher* pCipher = factory.createCipher(EVPKey);
    //Cipher* pRSACipher = factory.createCipher(RSAKey(RSAKey::KL_1024, RSAKey::EXP_SMALL));
    Cipher* pEVPCipher = factory.createCipher(EVPKey);

    std::string plainText = "This is my secret information";
    std::string encrypted = pEVPCipher->encryptString(plainText, Cipher::ENC_BASE64);
    std::string decrypted = pEVPCipher->decryptString(encrypted, Cipher::ENC_BASE64);

    // Create an output stream that will encrypt all data going through it
// and write pass it to the underlying file stream.
    Poco::FileOutputStream sink("encrypted.dat");
    CryptoOutputStream encryptor(sink, pEVPCipher->createEncryptor());

    Poco::FileInputStream source("source.txt");
    Poco::StreamCopier::copyStream(source, encryptor);

    // Always close output streams to flush all internal buffers
    encryptor.close();
    sink.close();
   /* std::shared_ptr<Value> v=ValueFactory::create(5);
    v->print();*/
    std::shared_ptr<Model> model= ModelFactory::createModel("Test");
    //DesignSet sols;
    VariableSet vars;
    //Variable1 var("x");
    //Constraint C("x");
    model->addParameter("x",1.)
         ->addParameter("y",0.);
    //model->SetVariable("x");
    //model->SetConstraint("y");
    //model->SetObjective("y");
    /*std::string name("x");
    vars.add("x",1.);
    vars.add("y",8);
    vars.add("z","Hello");*/
    auto x = vars.getValue("x");
    auto y = vars.getValue("y");
    auto z = vars.getValue("z");

    //int ff=std::any_cast<int>(v->getValue());

    std::shared_ptr<Value> v1 = ValueFactory::create(std::vector<int>{ 5 });
    v1->print();

    //std::cout << v->getType().name() << std::endl;
    //std::cout << v1->getType().name() << std::endl;
   /* std::shared_ptr<Derived<int>> der= std::make_shared<Derived<int>>(1);
    std::shared_ptr<TestDerived> testDer(new TestDerived());
    testDer->setValue(der);
    int v=testDer->getValue<int>();*/
    return 0;
}