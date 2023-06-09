#!/bin/sh
#

BASH_BASE_SIZE=0x00001a0e
CISCO_AC_TIMESTAMP=0x0000000061982626
CISCO_AC_OBJNAME=iseposture_install.sh                                           
# BASH_BASE_SIZE=0x00000000 is required for signing
# the comment is after or else the code signing tool will find the comment

version() { echo "$@" | awk -F. '{ printf("%d%03d%05d\n", $1,$2,$3); }'; }

ANYCONNECT_INSTPREFIX="/opt/cisco/anyconnect"
ANYCONNECT_BINDIR="${ANYCONNECT_INSTPREFIX}/bin"
ANYCONNECT_LIBDIR="${ANYCONNECT_INSTPREFIX}/lib"
ANYCONNECT_PLUGINDIR="${ANYCONNECT_BINDIR}/plugins"
ISEPOSTURE_PROFILEDIR="${ANYCONNECT_INSTPREFIX}/iseposture"
ISEPOSTURE_SCRIPTDIR="${ISEPOSTURE_PROFILEDIR}/scripts"

ISEBINFILES="aciseposture aciseagentd iseposture_uninstall.sh manifesttool_iseposture"
ISELIBFILES="libacise.so"
ISEPLUGINFILES="libacisectrl.so libaciseshim.so"
ISEPOSTUREMANIFEST="ACManifestISEPosture.xml"
VPNMANIFEST="${ANYCONNECT_INSTPREFIX}/ACManifestVPN.xml"

LOGFNAME=`date "+anyconnect-linux64-4.10.04065-iseposture-%H%M%S%d%m%Y.log"`
CLIENTNAME="Cisco AnyConnect ISE Posture Module"
CURRENTDIR=`dirname $0 2> /dev/null`

INST_BINDIR="${CURRENTDIR}/bin"
INST_PLUGINDIR="${INST_BINDIR}/plugins"
INST_LIBDIR="${CURRENTDIR}/lib"

ARG_NO_LICENSE=0

if [ "x$1" = "x--no-license" ]; then
    ARG_NO_LICENSE=1
fi

echo "Installing ${CLIENTNAME}..."
echo "Installing ${CLIENTNAME}..." > /tmp/${LOGFNAME}
echo `whoami` "invoked $0 from " `pwd` " at " `date` >> /tmp/${LOGFNAME}

# Check for root privileges
if [ `id | sed -e 's/(.*//'` != "uid=0" ]; then
  echo "Sorry, you need super user privileges to run this script."
  echo "Sorry, you need super user privileges to run this script." >> /tmp/${LOGFNAME}
  exit 1
fi

# ISE Posture requires VPN to be installed. We check the presence of the vpn manifest file to check if it is installed.
if [ ! -f ${VPNMANIFEST} ]; then
    echo "VPN should be installed before ISE Posture installation. Install VPN to proceed."
    echo "Exiting now."
    echo "VPN should be installed before ISE Posture installation. Install VPN to proceed." >> /tmp/${LOGFNAME}
    echo "Exiting now." >> /tmp/${LOGFNAME}
    exit 1
fi

failed=false
# version of ise posture being installed has to be same as installed VPN version
if [ -f "${CURRENTDIR}/${ISEPOSTUREMANIFEST}" ] && [ -f ${VPNMANIFEST} ]; then
    VPNVERSION=$(awk -F"\"" '/file version/ { print $2 }' ${VPNMANIFEST})
    ISECURRVERSION=$(awk -F"\"" '/file version/ { print $2 }' ${CURRENTDIR}/${ISEPOSTUREMANIFEST})

    if [ $(version $VPNVERSION) -ne $(version $ISECURRVERSION) ]; then
     failed=true
    fi
fi

if [ "$failed" = true ]; then
    echo "Please use ise posture installer from Anyconnect package with version ${VPNVERSION} for the installation"
    echo "Please use ise posture installer from Anyconnect package with version ${VPNVERSION} for the installation" >> /tmp/${LOGFNAME}
    echo "Exiting now."
    echo "Exiting now." >> /tmp/${LOGFNAME}
    exit 1
fi

if [ "x${ARG_NO_LICENSE}" = "x1" ]; then
    echo "Skipping license text ..."
else
    if [ -f "license.txt" ]; then
        cat ./license.txt
        echo
        echo -n "Do you accept the terms in the license agreement? [y/n] "
        read LICENSEAGREEMENT
        while :
        do
          case ${LICENSEAGREEMENT} in
               [Yy][Ee][Ss] | [Yy])
                       echo "You have accepted the license agreement."
                       echo "Please wait while ${CLIENTNAME} is being installed..."
                       break
                       ;;
               [Nn][Oo] | [Nn])
                       echo "The installation was cancelled because you did not accept the license agreement."
                       echo "The installation was cancelled because you did not accept the license agreement." >> /tmp/${LOGFNAME}
                       exit 1
                       ;;
               *)
                       echo "Please enter either \"y\" or \"n\"."
                       read LICENSEAGREEMENT
                       ;;
          esac
        done
    else
        echo "License file not found. Aborting installation."
        echo "License file not found. Aborting installation." >> /tmp/${LOGFNAME}
        exit 1
    fi
fi
if [ -x "/usr/bin/install" ]; then
    INSTALL="/usr/bin/install"
elif [ -x "/bin/install" ]; then
    INSTALL="/bin/install"
elif [ -x "/usr/local/bin/install" ]; then
    INSTALL="/usr/local/bin/install"
else
    INSTALL="install"
fi

${INSTALL} --help 2> /dev/null > /dev/null
if [ $? != 0 ]; then
    INSTALL=""
fi

echo "Creating directories... "
echo "Creating directories... " >> /tmp/${LOGFNAME}

if [ "x${INSTALL}" = "x" ]; then
    echo "Unable to find install command. Aborting installation."
    echo "Unable to find install command. Aborting installation." >> /tmp/${LOGFNAME}
    exit 1
fi

# Make sure destination directories exist
echo "Installing "${ANYCONNECT_BINDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${ANYCONNECT_BINDIR} || exit 1
echo "Installing "${ANYCONNECT_LIBDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${ANYCONNECT_LIBDIR} || exit 1
echo "Installing "${ANYCONNECT_PLUGINDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${ANYCONNECT_PLUGINDIR} || exit 1
echo "Installing "${ISEPOSTURE_PROFILEDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${ISEPOSTURE_PROFILEDIR} || exit 1
echo "Installing "${ISEPOSTURE_SCRIPTDIR} >> /tmp/${LOGFNAME}
${INSTALL} -d ${ISEPOSTURE_SCRIPTDIR} || exit 1

echo "done."
echo "done." >> /tmp/${LOGFNAME}

echo "Copying files... "
echo "Copying files... " >> /tmp/${LOGFNAME}

for f in ${ISEBINFILES}; do
    echo "Installing "${INST_BINDIR}/$f >> /tmp/${LOGFNAME}
    ${INSTALL} -o root -m 755 ${INST_BINDIR}/$f ${ANYCONNECT_BINDIR} || exit 1
done

for f in ${ISELIBFILES}; do
    echo "Installing "${INST_LIBDIR}/$f >> /tmp/${LOGFNAME}
    ${INSTALL} -o root -m 755 ${INST_LIBDIR}/$f ${ANYCONNECT_LIBDIR} || exit 1
done

for f in ${ISEPLUGINFILES}; do
    echo "Installing "${INST_PLUGINDIR}/$f >> /tmp/${LOGFNAME}
    ${INSTALL} -o root -m 755 ${INST_PLUGINDIR}/$f ${ANYCONNECT_PLUGINDIR} || exit 1
done

echo "done."
echo "done." >> /tmp/${LOGFNAME}

# update manifest
echo "Updating AC manifest." >> /tmp/${LOGFNAME}

${INSTALL} -o root -m 755 ${CURRENTDIR}/${ISEPOSTUREMANIFEST} ${ANYCONNECT_INSTPREFIX} >> /tmp/${LOGFNAME}
${INST_BINDIR}/manifesttool_iseposture -i ${ANYCONNECT_INSTPREFIX} ${ANYCONNECT_INSTPREFIX}/${ISEPOSTUREMANIFEST} >> /tmp/${LOGFNAME}

echo "done."
echo "done." >> /tmp/${LOGFNAME}

echo "${CLIENTNAME} is installed successfully."
echo "${CLIENTNAME} is installed successfully." >> /tmp/${LOGFNAME}

# move the logfile out of the tmp directory
mv /tmp/${LOGFNAME} ${ANYCONNECT_INSTPREFIX}/.

exit 0


  +S!cV!j!dqeayIVDMPT!A!kfkjvddSBJJJ!V!eznRGBF <0�80� ��SG!����_+��0	*�H�� 0r10	UUS10U
DigiCert Inc10Uwww.digicert.com110/U(DigiCert SHA2 Assured ID Code Signing CA0210317000000Z240321235959Z0v10	UUS10UMassachusetts10U
Boxborough10U
Cisco Systems, Inc.10UCisco Systems, Inc.0�"0	*�H�� � 0�
� �t�2�7)�7��%��}XA�1���%���'%����WR�<�_�vE�(�N��Wˏq�-�a��x�.��$�y@t��˕�-�N����k�kk��Jq��{��.��{��9���Yyr�B�И����T�k��{��L=����%��z�� �P��66{����� x�&���/�j����R؟ �+��t�<���7�h�[�X�h�㤹���h�s�i���[�etv�RZ�a6�=Q�V� ���0��0U#0�ZĹ{*
���q�`�-�euX0U:�ov݈4���[����H0U��0U%0
+0wUp0n05�3�1�/http://crl3.digicert.com/sha2-assured-cs-g1.crl05�3�1�/http://crl4.digicert.com/sha2-assured-cs-g1.crl0KU D0B06	`�H��l0)0'+http://www.digicert.com/CPS0g�0��+x0v0$+0�http://ocsp.digicert.com0N+0�Bhttp://cacerts.digicert.com/DigiCertSHA2AssuredIDCodeSigningCA.crt0U�0 0	*�H�� � �!l�aia<�5ߛW�	긎F~��7��֝�� SI������e6�A�Yb<$�!6��)���A��p����D�>ˋ�E�yh
��SVz$w9V��F�Z����3�>/���3���N�
-���� A�T#��s�Nˡ���zU|�&�ιkv�l��H2}.�G4�QF�ꁇ�m�z���~W�
]A�S���/k�*Sr�����9�B�\Q8n�(�R�!�8QUbʥX��Gi8�Of����k9�y�7� 40�00��	_ջfuSC�o�P0	*�H�� 0e10	UUS10U
DigiCert Inc10Uwww.digicert.com1$0"UDigiCert Assured ID Root CA0131022120000Z281022120000Z0r10	UUS10U
DigiCert Inc10Uwww.digicert.com110/U(DigiCert SHA2 Assured ID Code Signing CA0�"0	*�H�� � 0�
� �ӳ�gw�1I���E��:�D�娝�2�q�v�.����C�����7׶�𜆥�%�y(:~��g���)'��{#��#��w����#fT3Pt�(&�$i��R�g��E�-���, ��J����M`��Ĳ�p1f3q>�p����|˒��;1���
�W�J��t�+�l�~t96���N���j
���gN����� %#�d>R����Ŏ���,Q�s����b�sA��8�js �ds<���3���%�� ���0��0U�0� 0U��0U%0
+0y+m0k0$+0�http://ocsp.digicert.com0C+0�7http://cacerts.digicert.com/DigiCertAssuredIDRootCA.crt0��Uz0x0:�8�6�4http://crl4.digicert.com/DigiCertAssuredIDRootCA.crl0:�8�6�4http://crl3.digicert.com/DigiCertAssuredIDRootCA.crl0OU H0F08
`�H��l 0*0(+https://www.digicert.com/CPS0
`�H��l0UZĹ{*
���q�`�-�euX0U#0�E뢯��˂1-Q���!��m�0	*�H�� � >�Z$��"��,|%)v�]-:��0a�~`��=į���*� U7���ђuQ�n��Z�^$�N��?q�cK��_Dy�6���FN\��������Q$�$��'*�)(:q(<.���%�G�zhh���\ \�q������h��@�@D���d%B2�6�$�/r~�IE��Y��tdk��fCڳ������ Ι1c=���OƓ�������I�bn�S���.���hlD2�f����dQ�  j)�kE~<��nE��Y!���� ��I�
-Q�
r�{�=#�Wo�$�'b��"O���Q�=T�dB����o�$�;��9���J�L�&���S�~�Sp��@Gz��w��#��Â\V;��"�[{S�@��� �*�y��x�?t��g�V�t����k�f��m��|��Õ������y�&��hg/k��G,($��q	6İv��*o�Z"ϧi�����m�4����1z��n�g���?9w��K��^�Z��  Q���Qx?�����1��O�$��{<�_U���~���70�s�W�|lol���+M<I4�[�Ö���f-fA`>98u��c��wt����44HY&Q���5�λM-�mo�͇�u��1����s�R�o�V^ա5��UةJsrh���v�'��C�r�mN��-���~���@C����5)*L�\�S��i	q����]�)ߓ��!����+8�r�9�*&�[�9[���Z��B�~��'�B��