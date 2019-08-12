#ifndef REST_ITERATOR_H
#define REST_ITERATOR_H

namespace ara
{
namespace rest
{

    template <typename IterT>
    class IteratorRange
    {
    public:
        /**
         * \brief   Type of the underlying pair of iterators.
         *
         * \satisfy [SWS_REST_02383] Syntax Requirement for ara::rest::IteratorRange::Iterator.
         */
        using Iterator = IterT;

    public:
        /**
         * \brief   Constructs an IteratorRange from a pair of iterators. For convenient construction, see MakeIteratorRange().
         *
         * \satisfy [SWS_REST_02383] Syntax Requirement for Constructor.
         */
        explicit IteratorRange(Iterator first, Iterator last) : begin_(first), end_(last) { }

    public:
        /**
         * \brief   Returns the start of the sequence.
         *
         * \satisfy [SWS_REST_02385] Syntax Requirement for ara::rest::IteratorRange::Begin.
         */
        Iterator Begin() const
        {
            return begin_;
        }

        /**
         * \brief   Returns the end of the sequence.
         *
         * \satisfy [SWS_REST_02386] Syntax Requirement for ara::rest::IteratorRange::End.
         */
        Iterator End() const
        {
            return end_;
        }

        /**
         * \brief   Non-member equivalent of IteratorRange::begin()
         *
         * \satisfy [SWS_REST_02387] Syntax Requirement for ara::rest::IteratorRange::Begin.
         */
        friend Iterator Begin(const IteratorRange &otherIterator)
        {
            return otherIterator.begin_;
        }

        /**
         * \brief   Non-member equivalent of IteratorRange::end()
         *
         * \satisfy [SWS_REST_02388] Syntax Requirement for ara::rest::IteratorRange::End.
         */
        friend Iterator End(const IteratorRange &otherIterator)
        {
            return otherIterator.end_;
        }

    private:
        Iterator begin_;
        Iterator end_;
    };

    }
}

#endif //REST_ITERATOR_H
