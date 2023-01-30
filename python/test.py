
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
            "spread": {
                "value": 0.0,
                "ticker": "spreadTicker"
            }
        }
    }
    try:
        qlp.SwapRateHelper().validate(schema)
        print("Success")
    except Exception as e:
        print(e)


if __name__ == "__main__":
    main()
