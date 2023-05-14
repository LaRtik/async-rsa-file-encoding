#include "rsa.h"

RSA::Keys RSA::calculateRSAKeys() {
  std::vector<largeIntegerType> primes(1034);
  std::ifstream fin("primes.txt");
  for (int i = 0; i < 1033; i++) {
    int temp;
    fin >> temp;
    primes[i] = temp;
  }

  largeIntegerType p = primes[rand() % 1033];
  largeIntegerType q = primes[rand() % 1033];

  largeIntegerType n = p * q;

  largeIntegerType functionE = (p - 1) * (q - 1);

  largeIntegerType e = 1;
  for (largeIntegerType i = functionE - 1; i > 0; --i) {
    if (gcd(i, functionE) == 1 && prime(i)) {
      e = i;
      break;
    }
  }

  largeIntegerType d;
  for (largeIntegerType i = 0;; ++i) {
    if ((largeIntegerType)i * (largeIntegerType)e %
            (largeIntegerType)functionE ==
        1) {
      d = i;
      break;
    }
  }

  RSA::Keys keys{std::pair<largeIntegerType, largeIntegerType>{e, n},
                 std::pair<largeIntegerType, largeIntegerType>{d, n}};
  return keys;
}

largeIntegerType
RSA::cryptData(largeIntegerType data,
               std::pair<largeIntegerType, largeIntegerType> _publicKey) {
  return fastPow(data, _publicKey.first, _publicKey.second);
}

largeIntegerType
RSA::encryptData(largeIntegerType data,
                 std::pair<largeIntegerType, largeIntegerType> _privateKey) {
  return fastPow(data, _privateKey.first, _privateKey.second);
}

bool RSA::cryptMessage(
    std::vector<largeIntegerType> data,
    std::pair<largeIntegerType, largeIntegerType> _publicKey,
    std::string path) {
  std::ofstream fout(path + "/crypted_data", std::ios::out);
  char splitter = '\n';

  for (auto element : data) {
        auto msg = cryptData(element, _publicKey);
        for (const auto &c : std::to_string(msg))
          fout.write(&c, sizeof(c));
        fout.write(&splitter, sizeof(splitter));
  }

  fout.close();
  return true;
}

std::vector<largeIntegerType>
RSA::encryptMessage(std::vector<largeIntegerType> data,
                    std::pair<largeIntegerType, largeIntegerType> _privateKey) {
  clock_t start, end;
  start = clock();
  std::vector<largeIntegerType> encryptedMessage;
  std::vector<std::future<largeIntegerType>> futures;

  /* for (largeIntegerType element : data) {
      if (futures.size() > 100) {
          for (int i = 0; i < int(futures.size()); i++) {
              auto res = futures[i].get();
              encryptedMessage.push_back(res);
          }
          futures.clear();
      }
      futures.push_back(
          std::async(std::launch::async, &RSA::encryptData, this, element,
  _privateKey));
  }

  for (int i = 0; i < int(futures.size()); i++) {
      auto res = futures[i].get();
      encryptedMessage.push_back(res);
  }
*/
  for (const auto &d : data) {
        encryptedMessage.push_back(encryptData(d, _privateKey));
  }

  end = clock();
  qDebug() << double(end - start) / CLOCKS_PER_SEC;

  return encryptedMessage;
}

std::vector<largeIntegerType>
RSA::confuseData(std::vector<std::string> data,
                 std::pair<largeIntegerType, largeIntegerType> _anyKey) {
  std::vector<largeIntegerType> confusedData;
  confusedData.reserve(data.size());
  if (data.size() == 0) {
        return confusedData;
  }

  // largeIntegerType startValue = rand() % 10000 + 100;
  // confusedData.push_back(startValue);

  for (int i = 0; i < int(data.size()); ++i) {
        confusedData.push_back(std::stoll(data[i]));
  }
  return confusedData;
}

std::vector<std::string>
RSA::deconfuseData(std::vector<largeIntegerType> confusedData,
                   std::pair<largeIntegerType, largeIntegerType> _anyKey) {
  std::vector<std::string> data;

  for (auto d : confusedData) {
        data.push_back(std::to_string(d));
  }

  return data;
}
