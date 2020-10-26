void setup()

{ Serial.begin(115200);

  pinMode(14, OUTPUT);

  delay(2000);
}

void loop()

{ while (Serial.available())

  { char Rdata;

    Rdata = Serial.read();

    if (Rdata == 'A' | Rdata == 'a')

    { digitalWrite(14, HIGH);

      delay(50);
    }

    else if (Rdata == 'B' | Rdata == 'b')

    { digitalWrite(14, LOW);

      delay(10);

      digitalWrite(14, HIGH);

      delay(10);

      digitalWrite(14, LOW);
    }

    else

    {
      digitalWrite(14, LOW);
    }
  }
}
