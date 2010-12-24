Dokumentacija:
http://www.boostpro.com/writing/bpl.html#development-history

Reikalavimai:

.. code-block:: sh
  # the basic boost library
  sudo apt-get install libboost-dev

  # install the boost.python library
  sudo apt-get install libboost-python-dev

  # install the boost build tool: bjam
  sudo apt-get install boost-build

  # install MPFR library
  sudo apt-get install libmpfr-dev

Darbai:

* Suformuoti tikslumo (dvejetainiais skaitmenimis) taisykles.

Kompiliavimas:

.. code-block:: sh
  make                                  # Sukompiliuoja python modulį.
  python test.py                        # Įvykdo mini Python pavyzdį.
  make prog                             # Sukompiliuoja C++ programą.
  ./prog                                # Įvykdo mini C++ „testus“.
