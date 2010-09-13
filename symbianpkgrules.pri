!symbian: error(Only include this file for Symbian platforms)


vendorinfo = \
    "; Localised Vendor name" \
    "%{\"Nokia, Qt\"}" \
    " " \
    "; Unique Vendor name" \
    ":\"Nokia, Qt\"" \
    " "

default_deployment.pkg_prerules += vendorinfo

isEmpty(ICON):ICON = qt.svg
