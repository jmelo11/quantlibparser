
import QuantLibParser as qlp


def main():
    schema = {
           "helperType": "TenorBasis",
            "helperConfig": {
                "tenor": "1Y",
                "shortIndex": "LIBOR1M",
                "longIndex": "LIBOR3M",
                "spreadOnShort": True
            },
            "marketConfig": {                
                "spread":{
                    "value": 0.0,
                    "ticker": "spreadTicker"
                }                
            }     
    }
    try:
        qlp.TenorBasisSwapHelper().validate(schema)
    except Exception as e:
        print(e)
    finally:
        print("OK")


if __name__ == "__main__":
    main()
