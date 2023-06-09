#!/bin/sh
#

BASH_BASE_SIZE=0x00000b32
CISCO_AC_TIMESTAMP=0x0000000061982626
CISCO_AC_OBJNAME=iseposture_uninstall.sh                                         
# BASH_BASE_SIZE=0x00000000 is required for signing
# the comment is after or else the code signing tool will find the comment

ANYCONNECT_INSTPREFIX="/opt/cisco/anyconnect"
ANYCONNECT_BINDIR="${ANYCONNECT_INSTPREFIX}/bin"
ANYCONNECT_LIBDIR="${ANYCONNECT_INSTPREFIX}/lib"
ANYCONNECT_PLUGINDIR="${ANYCONNECT_BINDIR}/plugins"
ISEPOSTURE_PROFILEDIR="${ANYCONNECT_INSTPREFIX}/iseposture"
ISEPOSTURE_SCRIPTDIR="${ISEPOSTURE_PROFILEDIR}/scripts"


LOGDIR="/var/log/anyconnect"
LOG="${LOGDIR}/iseposture-uninstall.log"

ISEBINFILES="aciseposture aciseagentd iseposture_uninstall.sh manifesttool_iseposture"
ISELIBFILES="libacise.so"
ISEPLUGINFILES="libacisectrl.so libaciseshim.so"

# Create log directory if not exist
if [ ! -d ${LOGDIR} ]; then
  mkdir -p ${LOGDIR} >/dev/null 2>&1
fi

echo "Uninstalling Cisco AnyConnect ISE Posture Module..."
echo "Uninstalling Cisco AnyConnect ISE Posture Module..." > "${LOG}"
echo `whoami` "invoked $0 from " `pwd` " at " `date` >> "${LOG}"

# Check for root privileges
if [ `id | sed -e 's/(.*//'` != "uid=0" ]; then
  echo "Sorry, you need super user privileges to run this script."
  echo "Sorry, you need super user privileges to run this script." >> "${LOG}"
  exit 1
fi

# update the VPNManifest.dat
ISEPOSTUREMANIFEST="ACManifestISEPosture.xml"
echo "${ANYCONNECT_BINDIR}/manifesttool_iseposture -x ${ANYCONNECT_INSTPREFIX} ${ANYCONNECT_INSTPREFIX}/${ISEPOSTUREMANIFEST}" >> "${LOG}"
${ANYCONNECT_BINDIR}/manifesttool_iseposture -x ${ANYCONNECT_INSTPREFIX} ${ANYCONNECT_INSTPREFIX}/${ISEPOSTUREMANIFEST} >> "${LOG}"

rm -f ${ANYCONNECT_INSTPREFIX}/${ISEPOSTUREMANIFEST}

# Remove those pre-deploy files that we may have installed

for f in ${ISEBINFILES}; do
    if [ -e ${ANYCONNECT_BINDIR}/$f ]; then
       echo "rm -rf ${ANYCONNECT_BINDIR}/$f" >> "${LOG}"
       rm -rf ${ANYCONNECT_BINDIR}/$f >> "${LOG}" 2>&1
    fi
done

for f in ${ISELIBFILES}; do
    if [ -e ${ANYCONNECT_LIBDIR}/$f ]; then
       echo "rm -rf ${ANYCONNECT_LIBDIR}/$f" >> "${LOG}"
       rm -rf ${ANYCONNECT_LIBDIR}/$f >> "${LOG}" 2>&1
    fi
done

for f in ${ISEPLUGINFILES}; do
    if [ -e ${ANYCONNECT_PLUGINDIR}/$f ]; then
       echo "rm -rf ${ANYCONNECT_PLUGINDIR}/$f" >> "${LOG}"
       rm -rf ${ANYCONNECT_PLUGINDIR}/$f >> "${LOG}" 2>&1
    fi
done

echo "rm -rf ${ISEPOSTURE_SCRIPTDIR}" >> "${LOG}"
rm -rf ${ISEPOSTURE_SCRIPTDIR} >> "${LOG}" 2>&1

# Remove ISE Posture profile directory
# TODO AKK 3.2 FCS - Do this only for non-upgrade uninstall: rm -rf ${ISEPOSTURE_PROFILEDIR} >> "${LOG}" 2>&1


echo "Successfully removed Cisco AnyConnect ISE Posture Module from the system." >> "${LOG}"
echo "Successfully removed Cisco AnyConnect ISE Posture Module from the system."

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
���q�`�-�euX0U#0�E뢯��˂1-Q���!��m�0	*�H�� � >�Z$��"��,|%)v�]-:��0a�~`��=į���*� U7���ђuQ�n��Z�^$�N��?q�cK��_Dy�6���FN\��������Q$�$��'*�)(:q(<.���%�G�zhh���\ \�q������h��@�@D���d%B2�6�$�/r~�IE��Y��tdk��fCڳ������ Ι1c=���OƓ�������I�bn�S���.���hlD2�f����dQ�  2ϩS=(^�6��8��� �s��TM�s���_J �5�w��������3g|�3�l/t �&~��6����c	`��'��;eţ�J�8��S4���>�\y���";��ͮ�!�<�םڞu��vxnk�� ,^Yna��4��;meϡz�"��Vf1�m���up
����P7Uhɸ/�'�ѭ��WL&Fc	R:�稔�{n�5��K���U��0K���G��y��Fa��������̱(�I�  {o�jn(�E:�{�	I��Vc��ay�$/���H(Of�����e�?M��E�hlXr�dm�u�V���nw*5�Eb#�4�<�n�]_]q�H�51gh��z�Ι�1�
�/�R�r²0\Q��%���ȷ�U�N�?�f��G#J��'J����x��yui�ȻB˔��m������(NM�'l/U����?1@sb��!^|��"	e�.�����y!�:D��)�dI���k1P~�'P��V]���B*�V��s�X