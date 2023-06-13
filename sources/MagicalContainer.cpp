#include "MagicalContainer.hpp"
using namespace std;
using namespace ariel;

void MagicalContainer::addElement(int number)
{
    this->sortNumbers.insert(lower_bound(this->sortNumbers.begin(), this->sortNumbers.end(), number), number);
    updateVector();
}

int MagicalContainer::size()
{
    return this->sortNumbers.size();
}

void MagicalContainer::removeElement(int number)
{
    auto elmToRemove = std::find(this->sortNumbers.begin(), this->sortNumbers.end(), number);
    if (elmToRemove == this->sortNumbers.end())
    {
        throw std::runtime_error("The number not in the sortNumbers");
    }
    this->sortNumbers.erase(elmToRemove);
    updateVector();
}

bool MagicalContainer::is_prime(int number)
{
    if (number == 1)
    {
        return false;
    }
    else if (number == 2)
    {
        return true;
    }
    else
    {
        for (int i = number -1; i > 1; i--)
        {
            if (number % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}

void MagicalContainer::updateVector()
{
    this->primes.clear();
    for (auto checkNumber = this->sortNumbers.begin(); checkNumber != this->sortNumbers.end(); ++checkNumber)
    {
        if (is_prime(*checkNumber))
        {
            this->primes.push_back(&(*checkNumber));
        }
    }
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : container(container), iteratorForContainer(container.sortNumbers.begin()), currNumber(0)
{
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &container) : container(container.container), iteratorForContainer(container.iteratorForContainer), currNumber(container.currNumber)
{
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &container)
{
    if (this != &container)
    {
        throw runtime_error("they have a different container and cannot assign an iterator like this");
    }
    this->container = container.container;
    this->iteratorForContainer = container.iteratorForContainer;
    this->currNumber = container.currNumber;
    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&container) noexcept
{
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &container) const
{
    if (!(is_same<decltype(this->iteratorForContainer), decltype(container.iteratorForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumber == container.currNumber;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &container) const
{
    return !(this->currNumber == container.currNumber);
}

int MagicalContainer::AscendingIterator::operator*()
{
    if (this->iteratorForContainer == this->container.sortNumbers.end())
    {
        throw std::runtime_error("iterator is out of container");
    }

    return *(this->iteratorForContainer);
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (this->iteratorForContainer == this->container.sortNumbers.end())
    {
        throw std::runtime_error("iterator is out of container");
    }

    this->currNumber++;
    this->iteratorForContainer++;

    return *this;
}

bool MagicalContainer::AscendingIterator::operator>(AscendingIterator &container) const
{
    if (!(is_same<decltype(this->iteratorForContainer), decltype(container.iteratorForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumber > container.currNumber;
}

bool MagicalContainer::AscendingIterator::operator<(AscendingIterator &container) const
{
    if (!(is_same<decltype(this->iteratorForContainer), decltype(container.iteratorForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumber < container.currNumber;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    this->currNumber = 0;
    this->iteratorForContainer = this->container.sortNumbers.begin();
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    this->currNumber = this->container.sortNumbers.size();
    this->iteratorForContainer = this->container.sortNumbers.end();
    return *this;
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &container) : container(container.container), iteratorForContainer(container.iteratorForContainer), currNumber(container.currNumber)
{
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : container(container), iteratorForContainer(container.primes.begin()), currNumber(0)
{
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &container)
{
    if (this != &container)
    {
        throw runtime_error("they have a different container and cannot assign an iterator like this");
    }
    this->container = container.container;
    this->iteratorForContainer = container.iteratorForContainer;
    this->currNumber = container.currNumber;
    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&container) noexcept
{
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &container) const
{
    if (!(is_same<decltype(this->iteratorForContainer), decltype(container.iteratorForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumber == container.currNumber;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &container) const
{
    return !(this->currNumber == container.currNumber);
}

int MagicalContainer::PrimeIterator::operator*()
{
    if (this->iteratorForContainer == this->container.primes.end())
    {
        throw std::runtime_error("iterator is out of container");
    }

    return **(this->iteratorForContainer);
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (this->iteratorForContainer == this->container.primes.end())
    {
        throw std::runtime_error("iterator is out of container");
    }

    ++this->currNumber;
    ++this->iteratorForContainer;

    return *this;
}

bool MagicalContainer::PrimeIterator::operator>(PrimeIterator &container) const
{
    if (!(is_same<decltype(this->iteratorForContainer), decltype(container.iteratorForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumber > container.currNumber;
}

bool MagicalContainer::PrimeIterator::operator<(PrimeIterator &container) const
{
    if (!(is_same<decltype(this->iteratorForContainer), decltype(container.iteratorForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumber < container.currNumber;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    this->currNumber = 0;
    this->iteratorForContainer = this->container.primes.begin();
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    this->currNumber = this->container.primes.size();
    this->iteratorForContainer = this->container.primes.end();
    return *this;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &container) : container(container.container), iteratorStartForContainer(container.iteratorStartForContainer), iteratorEndForContainer(container.iteratorEndForContainer), currNumberStart(container.currNumberStart), currNumberEnd(container.currNumberEnd), counter(0)
{
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : container(container), iteratorStartForContainer(container.sortNumbers.begin()), iteratorEndForContainer(container.sortNumbers.rbegin()), currNumberStart(0), currNumberEnd(container.sortNumbers.size() - 1), counter(0)
{
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &container)
{
    if (this != &container)
    {
        throw runtime_error("they have a different container and cannot assign an iterator like this");
    }
    this->container = container.container;
    this->iteratorStartForContainer = container.iteratorStartForContainer;
    this->iteratorEndForContainer = container.iteratorEndForContainer;
    this->currNumberStart = container.currNumberStart;
    this->currNumberEnd = container.currNumberEnd;
    this->counter = container.counter;
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&container) noexcept
{
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &container) const
{
    if (!(is_same<decltype(this->iteratorStartForContainer), decltype(container.iteratorStartForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    if (!(is_same<decltype(this->iteratorEndForContainer), decltype(container.iteratorEndForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return ((this->currNumberStart == container.currNumberStart) && (this->currNumberEnd == container.currNumberEnd));
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &container) const
{
    return !((this->currNumberStart == container.currNumberStart) && (this->currNumberEnd == container.currNumberEnd));
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    if (this->container.sortNumbers.size() != 0)
    {
        if (this->currNumberEnd < this->currNumberStart)
        {
            throw std::runtime_error("the end iterator bigger than start iterator");
        }
    }
    if (this->counter % 2 == 0)
    {
        return *(this->iteratorStartForContainer);
    }
    return *(this->iteratorEndForContainer);
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (this->container.sortNumbers.size() != 0)
    {
        if (this->currNumberEnd < this->currNumberStart)
        {
            throw std::runtime_error("the end iterator bigger than start iterator");
        }
    }
    if (this->counter % 2 == 0)
    {
        ++this->iteratorStartForContainer;
        this->currNumberStart++;
        this->counter++;
        return *this;
    }
    this->currNumberEnd--;
    ++this->iteratorEndForContainer;
    this->counter++;
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator>(SideCrossIterator &container) const
{
    if (!(is_same<decltype(this->iteratorStartForContainer), decltype(container.iteratorStartForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    if (!(is_same<decltype(this->iteratorEndForContainer), decltype(container.iteratorEndForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumberStart > container.currNumberStart;
}

bool MagicalContainer::SideCrossIterator::operator<(SideCrossIterator &container) const
{
    if (!(is_same<decltype(this->iteratorStartForContainer), decltype(container.iteratorStartForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    if (!(is_same<decltype(this->iteratorEndForContainer), decltype(container.iteratorEndForContainer)>::value))
    {
        throw std::invalid_argument("they have a different container and cannot assign an iterator like this");
    }
    return this->currNumberStart < container.currNumberStart;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    this->currNumberStart = 0;
    this->iteratorStartForContainer = this->container.sortNumbers.begin();
    this->currNumberEnd = this->container.sortNumbers.size() - 1;
    this->iteratorEndForContainer = this->container.sortNumbers.rbegin();
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    if (this->container.sortNumbers.size() % 2 != 0)
    {
        this->currNumberStart = this->container.sortNumbers.size() / 2 + 1;
        this->currNumberEnd = this->container.sortNumbers.size() / 2;
        advance(this->iteratorEndForContainer, this->currNumberEnd);
        advance(this->iteratorStartForContainer, this->currNumberStart);
        return *this;
    }
    this->currNumberEnd = this->container.sortNumbers.size() / 2 - 1;
    this->currNumberStart = this->container.sortNumbers.size() / 2;
    advance(this->iteratorEndForContainer, this->currNumberEnd);
    advance(this->iteratorStartForContainer, this->currNumberStart);
    return *this;
}
